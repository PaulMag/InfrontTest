#include "DupFileFinder.h"

#include <iostream>
#include <string>
#include <fstream>
using namespace std;


DupFileFinder::DupFileFinder()
{
}

DupFileFinder::~DupFileFinder()
{
}

void DupFileFinder::recursiveFind(path p)
{
	try
	{
		if (exists(p))
		{
			if (is_regular_file(p))
			{
				//cout << p << " size is " << file_size(p) << endl;
				for (int i=0; i<uniqueFiles.size(); i++) {
					if (uniqueFiles[i].isDuplicateOf(p)) {
						uniqueFiles[i].addPath(p);
						return;  // duplicate found; stop search
					}
				}
				uniqueFiles.push_back(UniqueFile(p));  // if no duplicate found
			}
			else if (is_directory(p))
			{
				//cout << p << " is a directory" << endl;
				std::vector<path> v;
				for (auto&& x : directory_iterator(p))
					recursiveFind(x.path());
			}
			else
				cout << p << " exists, but is not a regular file or directory and is ignored." << endl;
		}
		else
			cout << p << " does not exist" << endl;
	}
	catch (const filesystem_error& ex)
	{
		cout << ex.what() << endl;
	}
}

bool operator<(const UniqueFile& a, const UniqueFile& b)
{
	if (a.name < b.name)
		return true;
	else
		return false;
}

void DupFileFinder::sort()
{
	std::sort(uniqueFiles.begin(), uniqueFiles.end());
	for (int i=0; i<uniqueFiles.size(); i++)
		uniqueFiles[i].sort();
}

void DupFileFinder::group()
/* Group identical sets of files, meaning files that are present in all the same directories. */
{
	int counter = uniqueFiles.size();
	for (int i=1; i<uniqueFiles.size(); i++)
		for (int j=0; j<i; j++)
		{
			if (uniqueFiles[j].isGrouped)
				continue;
			if (uniqueFiles[j].directories == uniqueFiles[i].directories) {
				uniqueFiles[j].namesGrouped.push_back(uniqueFiles[i].name);
				uniqueFiles[i].isGrouped = true;
				counter--;
				break;
			}
		}
	vector<UniqueFile> temp;
	temp.reserve(counter);
	for (int i=0; i<uniqueFiles.size(); i++)
		if (not uniqueFiles[i].isGrouped)
			temp.push_back(uniqueFiles[i]);
	uniqueFiles = temp;
}

void DupFileFinder::writeToFile(string p)
{
	std::ofstream outFile;
	outFile.open(p);
	for (auto uf : uniqueFiles)
		outFile << uf.getString();
	outFile.close();
}

void DupFileFinder::display()
{
	for (auto uf : uniqueFiles)
		cout << uf.getString();
}
