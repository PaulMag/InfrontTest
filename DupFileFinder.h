#pragma once

#include "UniqueFile.h"


class DupFileFinder
{
public:
	DupFileFinder();
	~DupFileFinder();

	std::vector<UniqueFile> uniqueFiles;

	void recursiveFind(path p);
	void removeNonDups();
	void sort();
	void group();
	void writeToFile(string p);
	void display();
};

