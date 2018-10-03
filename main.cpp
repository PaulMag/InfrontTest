#include <iostream>
#include <string>
using namespace std;

#include "DupFileFinder.h"


int main()
{
	string dirname;
	cout << "Directory to search for duplicate files (default '.'): ";
	getline(cin, dirname);
	if (dirname.size() == 0)
		dirname = ".";
	
	DupFileFinder d;
	d.recursiveFind(dirname);
	d.sort();
	d.group();
	d.display();
	cout << endl;

	string outFileName;
	cout << "Write results to file (default './RESULTS.txt'): ";
	getline(cin, outFileName);
	cout << "Writing to file " << outFileName << endl;
	if (outFileName.size() == 0)
		outFileName = "RESULTS.txt";
	d.writeToFile(outFileName);

	return 0;
}
