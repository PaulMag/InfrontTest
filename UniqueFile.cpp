#include "UniqueFile.h"

#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <algorithm>


bool compareFiles(const std::string& p1, const std::string& p2) {
	std::ifstream f1(p1, std::ifstream::binary | std::ifstream::ate);
	std::ifstream f2(p2, std::ifstream::binary | std::ifstream::ate);

	if (f1.fail() || f2.fail()) {
		return false; //file problem
	}

	if (f1.tellg() != f2.tellg()) {
		return false; //size mismatch
	}

	//seek back to beginning and use std::equal to compare contents
	f1.seekg(0, std::ifstream::beg);
	f2.seekg(0, std::ifstream::beg);
	return std::equal(std::istreambuf_iterator<char>(f1.rdbuf()),
		std::istreambuf_iterator<char>(),
		std::istreambuf_iterator<char>(f2.rdbuf()));
}


UniqueFile::UniqueFile(path p)
{
	name = p.filename();
	size = file_size(p);
	directories.push_back(p.parent_path());
}

UniqueFile::~UniqueFile()
{
}

void UniqueFile::addPath(path p)
{
	directories.push_back(p.parent_path());
}

bool UniqueFile::isDuplicateOf(path p)
{
	if (name.compare(p.filename()) == 0 and size == file_size(p))
	{
		path comparepath;
		comparepath.append(directories[0].string()).append(name.string());
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
