#pragma once

#include <vector>
using namespace std;

#include <boost/filesystem.hpp>
using namespace boost::filesystem;

#include "UniqueFile.h"


class DupFileFinder
{
public:
	DupFileFinder();
	~DupFileFinder();

	std::vector<path> files;
	std::vector<UniqueFile> uniqueFiles;

	void recursiveFind(path p);
	void sort();
	void writeToFile(string p);
	void display();
};

