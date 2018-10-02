#include <iostream>
#include <string>
using namespace std;

#include <boost/filesystem.hpp>
using namespace boost::filesystem;

#include "DupFileFinder.h"


/*
bool operator<(const Person& a, const Person& b)
{
	if (a.name < b.name)
		return true;
	else
		return false;
}
*/

int main()
{
	// This comment makes the file 50 bytes larger!
	
	string dirname = "../../../Infront";
	path p = path(dirname);
	DupFileFinder d;
	d.recursiveFind(p);

	return 0;
}