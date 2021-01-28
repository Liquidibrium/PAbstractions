#include <iostream>
#include <string>
#include "simpio.h"
#include "console.h"
#include "vector.h"
#include "queue.h"
#include <time.h>
#include "lexicon.h"
#include "FileSystem.h"

using namespace std;

void printTestResults(bool passed, int testNum, int & passedCounter) {
	if (passed) {
		cout << "test " << testNum << " passed" << endl;
		passedCounter++;
	} else {
		cout << "test " << testNum << " failed" << endl;
	}
}

bool contains(Vector<string> &v, string name) {
	for (int i=0; i<v.size(); i++) {
		if (v[i] == name)
			return true;
	}
	return false;
}

bool runFileSystemTest(int num) {
	FileSystem * fs;
	Vector<string> files, folders; 
	bool passed = true;
	
	switch (num) {
		case 1: 
			fs = new FileSystem;
			return	fs->getActiveFolderName() == "root" && 
					fs->getFileList().size() == 0 && 
					fs->getFolderList().size() == 0;

		case 2:
			fs = new FileSystem;
			fs->createFolder("folder1");
			fs->createFolder("folder2");
			folders = fs->getFolderList();
			return	fs->getActiveFolderName() == "root" && 
					contains(folders, "folder1") && 
					contains(folders, "folder2") && 
					folders.size() == 2 &&
					fs->getFileList().size() == 0;

		case 3:
			fs = new FileSystem;
			fs->createFile("file1");
			fs->createFile("file2");
			files = fs->getFileList();
			return	fs->getActiveFolderName() == "root" && 
					contains(files, "file1") && 
					contains(files, "file2") && 
					files.size() == 2 &&
					fs->getFolderList().size() == 0;

		case 4:
			fs = new FileSystem;
			fs->createFile("file1");
			fs->createFile("file2");
			fs->createFile("file1");
			fs->createFolder("folder1");
			fs->createFile("file3");
			fs->createFolder("folder1");
			fs->up();
			files = fs->getFileList();
			folders = fs->getFolderList();
			return	fs->getActiveFolderName() == "root" && 
					contains(files, "file1") && 
					contains(files, "file2") && 
					contains(files, "file3") && 
					contains(folders, "folder1") &&
					files.size() == 3 &&
					folders.size() == 1;

		case 5:
			fs = new FileSystem;
			fs->createFolder("folder1");
			fs->createFolder("folder2");
			fs->createFolder("folder3");
			fs->createFile("file3");
			fs->createFile("file4");
			
			fs->selectFolder("folder2");

			fs->createFolder("folder4");
			fs->createFolder("folder2");
			fs->createFile("file1");
			fs->createFile("file4");

			files = fs->getFileList();
			folders = fs->getFolderList();
			return	fs->getActiveFolderName() == "folder2" && 
					contains(files, "file1") && 
					contains(files, "file4") && 
					contains(folders, "folder4") &&
					contains(folders, "folder2") &&
					files.size() == 2 &&
					folders.size() == 2;
		
		case 6:
			fs = new FileSystem;
			fs->createFolder("folder1");
			fs->createFolder("folder2");
			fs->createFile("file1");
			fs->createFile("file2");
			
			fs->selectFolder("folder2");
			fs->selectFolder("folder1");//no action on this command
			
			fs->createFolder("folder3");
			fs->createFile("file1");

			fs->selectFolder("folder3");

			fs->createFolder("folder1");
			fs->createFolder("folder2");
			fs->createFolder("folder3");
			fs->createFile("file1");
			fs->createFile("file2");
			fs->createFile("file2");

			files = fs->getFileList();
			folders = fs->getFolderList();
			passed =	fs->getActiveFolderName() == "folder3" &&
							contains(files, "file1") &&
							contains(files, "file2") &&
							contains(folders, "folder1") &&
							contains(folders, "folder2") &&
							contains(folders, "folder3") &&
							files.size() == 2 &&
							folders.size() == 3;

			fs->up();
			files = fs->getFileList();
			folders = fs->getFolderList();
			return	passed && fs->getActiveFolderName() == "folder2" && 
					contains(files, "file1") && 
					contains(folders, "folder3") && 
					files.size() == 1 &&
					folders.size() == 1;

		case 7:
			fs = new FileSystem;
			fs->createFolder("folder1");
			fs->createFolder("folder2");
			fs->createFile("file1");
			
			return	fs->getActiveFolderName() == "root" && 
					fs->searchFile("file1") == "file1";
		
		case 8:
			fs = new FileSystem;
			fs->createFolder("folder1");
			fs->createFolder("folder2");
			fs->createFile("file1");
			
			fs->selectFolder("folder2");
			
			fs->createFolder("folder3");
			fs->createFile("file1");

			fs->selectFolder("folder3");

			fs->createFolder("folder1");
			fs->createFolder("folder2");
			fs->createFolder("folder3");
			fs->createFile("file1");
			fs->createFile("file7");

			fs->up();
			fs->up();

			return	fs->getActiveFolderName() == "root" && 
					fs->searchFile("file7") == "folder2/folder3/file7";


		case 9:
			fs = new FileSystem;
			fs->createFolder("folder1");
			fs->createFolder("folder2");
			fs->createFile("file1");
			
			fs->selectFolder("folder2");
			
			fs->createFolder("folder3");
			fs->createFile("file21");

			fs->selectFolder("folder3");

			fs->createFolder("folder1");
			fs->createFolder("folder2");
			fs->createFolder("folder3");
			fs->createFile("file5");
			fs->createFile("file7");
			
			fs->selectFolder("folder3");
			fs->createFile("fileX");
			fs->up();
			fs->selectFolder("folder2");
			fs->createFile("fileY");

			fs->up();
			fs->up();
			fs->up();
			fs->up();
			return	fs->getActiveFolderName() == "root" && 
					fs->searchFile("file9") == "" && 
					fs->searchFile("file7") == "folder2/folder3/file7" && 
					fs->searchFile("fileX") == "folder2/folder3/folder3/fileX" &&
					fs->searchFile("fileY") == "folder2/folder3/folder2/fileY";

		case 10:
			fs = new FileSystem;
			fs->createFolder("folder1");
			fs->createFolder("folder2");
			fs->createFile("file1");
			
			fs->selectFolder("folder1");
			fs->createFolder("folder2");
			fs->createFile("file2");
			
			fs->up();
			fs->selectFolder("folder2");
			fs->createFolder("folder1");
			fs->createFolder("folder2");
			fs->createFolder("folder3");
			fs->createFile("file5");
			fs->createFile("file7");
			passed = fs->searchFile("file") == "" && fs->searchFile("file5") == "file5";

			fs->up();
			fs->selectFolder("folder1");
			passed = passed && fs->searchFile("file") == "" && fs->searchFile("file1") == "";
		
			fs->up();
			return	passed && fs->getActiveFolderName() == "root" && 
					fs->searchFile("file") == "" && 
					fs->searchFile("file7") == "folder2/file7";
	}

	return false;
}


void runFileSystemTests() {
	cout << "### Run File System tests ###" << endl;
	int passedNum = 0;
	int testNum = 1;

	for (; testNum<=10; testNum++) {
		bool res = runFileSystemTest(testNum);
		printTestResults(res, testNum, passedNum);
	}

	cout << "###### passed " << passedNum << " tests ######" << endl;
}

int main() {
	runFileSystemTests();
	return 0;
}