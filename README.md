# Infront C++ programming test

This is the solution of Infront's C++ programming test Level 3.

Author: Paul Magnus Sørensen-Clark

Date: 2018-10-03

## Build

The only libraries used are STL and Boost (filesystem module).

To build, open project_files/InfrontTestVS.vcxproj in VisualStudio and build, assuming you link a build of Boost.

Or, you could build the source files manually, assuming you link a build of Boost.

All necessary files are included in this folder (including a pre-compiled executable InfrontTestVS.exe).
You can also find the source files at 
https://github.com/PaulMag/InfrontTest
 
## Usage

Run InfrontTestVS.exe (either the included executable or the one you build yourself). A terminal window will appear and you will be prompted to write a file path to scan, or just hit enter to default to the current directory. The algorithm will run and display the results in the terminal. Then you are prompted to write a filepath to write the output in, or hit enter to use the default option RESULT.txt in the current folder. Output written to file is the same as displayed in the terminal.

## Assumptions

The full relative paths are part of the output. If you f.ex. scan the current directory each listed directory path will look like "./Directory A", etc. And files that exist directly in the current directoy will have the path "." listed.

The Level 2 text "check the content of the files to detect duplicates" could potentially be interpreted as we define duplicate files as having the same content INSTEAD of having the same filename and size, but I think the intention is that we define duplicate files as having the same filename AND size AND content, as this is more compatible with the Level 3 text, and so this is what I did.

In other words, files with different filenames, but identical content, are NOT considered duplicates and will be listed independently.
Files with identical filenames, but different content (and size) are also NOT considered duplicates.
Thus we can have the same filename show up multiple times in the final result. This means that we may have some files with the same names, but different content.

Level 3 I have understood as a group of files is defined as an identical set if and only if they are all present in the exact same directories. The files within a group can implicitly NOT be duplicates of eachother, as they would then be listed as the same file instead. And they can NOT have the same filename, as then they could not exist in the same directories.

## Structure

This program consist of a main file and two classes: UniqueFile and DupFileFinder.

One instance of UniqueFile represents ONE unique file and all its duplicates.
It contains a filename and size and a list of all directory paths that contains duplicates of this file.
It does not store the contents of the file, but instead has a method of checking if it is a duplicate of another file byte by byte.

After grouping identical sets of files only one UniqueFile instance will remain for each group of files, and this instance will contain the filename of the first (alphabetically) file and then a list of the remaining filenames (alphabetically) in this group.

The main file handles the user's input and calls the methods of DupFileFinder that constitutes the algorithm. DupFileFinder is only instanced once.

recursiveFind recursively iterates through the path provided by the user. For each file it finds it checks if it is a duplicate of any files it has found so far. If yes, it adds the new file's path to the existing UniqueFile instance. If not, it creates a new UniqueFile instance.

removeNonDups removes every instance of UniqueFile that only has one path, because then it is a non-duplicate file and should not appear in the output.

sort sorts the files by filename. It also sorts the list of paths within each UniqueFile.
If several files have the same filename they end up in no particular order.

group groups the identical sets of files.

## Platform compatibility

This application is Microsoft Windows compatible.
It has not been tested on other platforms.
