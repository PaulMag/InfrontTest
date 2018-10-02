#pragma once

#include <iostream>
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
	void addPath(path p);
	bool isDuplicateOf(path p);
	void display();

	path name;
	vector<path> directories;
};

