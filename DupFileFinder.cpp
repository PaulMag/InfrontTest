#include "DupFileFinder.h"

#include <iostream>
#include <fstream>
using namespace std;


DupFileFinder::DupFileFinder()
{
}

DupFileFinder::~DupFileFinder()
{
}

void DupFileFinder::recursiveFind(path p)
/* Recursively iterate through everything inside path p.
 * Peform different actions when finding a new unique file, a new duplicate file,
 * or a new directory.
 */
{
	try
	{
		if (exists(p))
		{
			if (is_regular_file(p))
			{
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
				std::vector<path> v;
				for (auto&& x : directory_iterator(p))
					recursiveFind(x.path());  // new directory found => recursion
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

void DupFileFinder::removeNonDups()
/* Remove every file that does not exist in at least 2 different directories. */
{
	vector<UniqueFile> temp;
	for (int i=0; i<uniqueFiles.size(); i++)
		if (uniqueFiles[i].directories.size() > 1)
			temp.push_back(uniqueFiles[i]);
	uniqueFiles = temp;
}

bool operator<(const UniqueFile& a, const UniqueFile& b)
{
	if (a.name < b.name)
		return true;
	else
		return false;
}
void DupFileFinder::sort()
/* Sort the UniqueFile instances after their filenames.
 * If several UniqueFiles exist with the same name (but different content)
 * their order is arbitrary.
 */
{
	std::sort(uniqueFiles.begin(), uniqueFiles.end());
	for (int i=0; i<uniqueFiles.size(); i++)
		uniqueFiles[i].sort();  // Sort each file's list of directories as well.
}

void DupFileFinder::group()
/* Group identical sets of files, meaning files that are present in all the same
 * directories. Delete the original instances of files that are grouped with
 * another file. Could do the deletion in the first loop, but that would lead to
 * a lot of reallocation of the vector.
 */
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
	temp.reserve(counter);  // not necessary, but for performance
	for (int i=0; i<uniqueFiles.size(); i++)
		if (not uniqueFiles[i].isGrouped)
			temp.push_back(uniqueFiles[i]);
	uniqueFiles = temp;
}

void DupFileFinder::writeToFile(string p)
/* Write the final result to an output file in a nice format. */
{
	std::ofstream outFile;
	outFile.open(p);
	for (auto uf : uniqueFiles)
		outFile << uf.getString();
	outFile.close();
}

void DupFileFinder::display()
/* Print the final result to terminal in a nice format. */
{
	for (auto uf : uniqueFiles)
		cout << uf.getString();
}
