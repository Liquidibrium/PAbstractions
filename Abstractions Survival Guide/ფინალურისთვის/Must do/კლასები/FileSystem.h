
#ifndef FILE_SYSTEM_H_
#define FILE_SYSTEM_H_

#include <string>
#include "vector.h"
#include "set.h"
#include "map.h"
using namespace std;

class FileSystem {

	public:

		FileSystem();
		~FileSystem();
		Vector<string> getFolderList();
		Vector<string> getFileList();
		bool createFolder(string name);
		bool createFile(string name);
		bool selectFolder(string name);

	private:

		struct File {
			string name;
		};

		struct Folder {
			string name;
			Set<Folder*> folders;
			Set<File*> files;
		};

		Set<string> folderNames;
		Set<string> fileNames;
		
		Vector<Folder*> folders;
		Vector<File*> files;

		Folder* activeFolder;

		void recGetList(Folder* curFolder, Vector<string> &list, bool needFolders);

		Folder* getNewActiveFolder(string &name);

};

#endif
