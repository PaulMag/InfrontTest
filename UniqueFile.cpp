#include "UniqueFile.h"

#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>


UniqueFile::UniqueFile(path p)
/* Should only be constructed when a new, unique file is found. */
{
	name = p.filename();
	size = file_size(p);
	directories.push_back(p.parent_path());
}

UniqueFile::~UniqueFile()
{
}

void UniqueFile::addPath(path p)
/* Adding a new directory path when a duplicate of this file was found. */
{
	directories.push_back(p.parent_path());
}

bool compareFiles(const std::string& p1, const std::string& p2)
/* Help function to isDuplicateOf.
 * Compares the content of two files, and stops as soon as a mismatch is found.
 */
{
	std::ifstream f1(p1, std::ifstream::binary | std::ifstream::ate);
	std::ifstream f2(p2, std::ifstream::binary | std::ifstream::ate);

	if (f1.fail() || f2.fail()) {
		return false; //file problem
	}

	//seek back to beginning and use std::equal to compare contents
	f1.seekg(0, std::ifstream::beg);
	f2.seekg(0, std::ifstream::beg);
	return std::equal(std::istreambuf_iterator<char>(f1.rdbuf()),
		std::istreambuf_iterator<char>(),
		std::istreambuf_iterator<char>(f2.rdbuf()));
}

bool UniqueFile::isDuplicateOf(path p)
/* Return true of filename AND file size AND file content is identical. */
{
	if (name.compare(p.filename()) == 0 and size == file_size(p))
	{
		path comparepath;
		comparepath.append(directories[0].string()).append(name.string());
		// Piece together full path with an arbitrary directory+filename.
		if (compareFiles(comparepath.string(), p.string()))
			return true;
	}
	return false;
}

void UniqueFile::sort()
{
	std::sort(directories.begin(), directories.end());
}

string UniqueFile::getString()
/* Create a nicely formatted string with filename
 * (and filename of any file in this group, being in the same directories)
 * and a list of all directories containing duplicates of this file.
 */
{
	string s = name.string();
	for (auto filename : namesGrouped) {
		s.append(", " + filename.string());
	}
	s.append("\n");
	for (auto dirname : directories) {
		s.append("    " + dirname.string() + "\n");
	}
	return s;
}

void UniqueFile::display()
{
	cout << getString();
}
