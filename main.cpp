#include <iostream>

#include "DupFileFinder.h"


int main()
{
	/// User decides a file system path to scan
	string dirname;
	cout << "Directory to search for duplicate files (default '.'): ";
	getline(cin, dirname);
	if (dirname.size() == 0)
		dirname = ".";  // default if empty string provided
	
	/// The algorithm
	DupFileFinder d;
	d.recursiveFind(dirname);
	d.removeNonDups();
	d.sort();
	d.group();
	d.display();
	cout << endl;

	/// User decides a file system path to write output
	string outFileName;
	cout << "Write results to file (default './RESULTS.txt'): ";
	getline(cin, outFileName);
	if (outFileName.size() == 0)
		outFileName = "RESULTS.txt";  // default if empty string provided
	cout << "Writing to file " << outFileName << endl;
	d.writeToFile(outFileName);

	return 0;
}
