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
					files.push_back(p);
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
