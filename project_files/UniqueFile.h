#pragma once

#include <string>
#include <vector>
using namespace std;

#include <boost/filesystem.hpp>
using namespace boost::filesystem;


class UniqueFile
{
public:
	UniqueFile(path p);
	~UniqueFile();

	path name;
	uintmax_t size;
	vector<path> directories;
	bool isGrouped = false;
	vector<path> namesGrouped;

	void addPath(path p);
	bool isDuplicateOf(path p);
	void sort();
	string getString();
	void display();
};

