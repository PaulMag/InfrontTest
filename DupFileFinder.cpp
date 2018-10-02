#include "DupFileFinder.h"

#include <iostream>
#include <string>
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
				files.push_back(p);
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
