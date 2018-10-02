#pragma once

#include <vector>
using namespace std;

#include <boost/filesystem.hpp>
using namespace boost::filesystem;


class DupFileFinder
{
public:
	DupFileFinder();
	~DupFileFinder();

	std::vector<path> files;

	void recursiveFind(path p);
};

