#include "UniqueFile.h"

#include <iostream>
#include <string>


UniqueFile::UniqueFile(path p)
{
	name = p.filename();
	directories.push_back(p.parent_path());
}

UniqueFile::~UniqueFile()
{
}

void UniqueFile::addPath(path p)
{
	directories.push_back(p.parent_path());
}

bool UniqueFile::isDuplicateOf(path p)
{
	if (name.compare(p.filename()) == 0)
		return true;
	else
		return false;
}

void UniqueFile::display()
{
	cout << name << " number: " << directories.size() << endl;
	for (auto dirname : directories) {
		cout << "    " << dirname << endl;
	}
}
