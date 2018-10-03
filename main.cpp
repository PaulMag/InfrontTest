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
	string dirname = "../../../Infront/dummy_files";
	path p = path(dirname);
	DupFileFinder d;
	d.recursiveFind(p);
	
	d.sort();
	d.group();

	d.display();
	cout << endl;

	cout << "Write results to file: ";
	string outFileName;
	cin >> outFileName;
	cout << "Writing to file " << outFileName << endl;
	d.writeToFile(outFileName);

	return 0;
}
