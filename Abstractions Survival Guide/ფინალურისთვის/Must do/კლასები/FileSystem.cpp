
#include "FileSystem.h"
#include "queue.h"

FileSystem::FileSystem() {
	activeFolder = NULL;
}

FileSystem::~FileSystem() {
	for (int i = 0; i < files.size(); i++)
		delete files[i];
	for (int j = 0; j < folders.size(); j++)
		delete folders[j];
}

void FileSystem::recGetList(Folder* curFolder, Vector<string> &list, bool needFolders) {
	if (curFolder == NULL) return;
	foreach(Folder* folder in curFolder->folders)
		recGetList(folder, list, needFolders);
	if (needFolders) list.add(curFolder->name);
	else
		foreach (File* file in curFolder->files)
			list.add(file->name);
}

Vector<string> FileSystem::getFolderList() {
	Vector<string> folderList;
	recGetList(activeFolder, folderList, true);
	folderList.remove(folderList.size() - 1);
	return folderList;
}

Vector<string> FileSystem::getFileList() {
	Vector<string> fileList;
	recGetList(activeFolder, fileList, false);
	return fileList;
}

bool FileSystem::createFolder(string name) {

	Folder* newFolder = new Folder;
	newFolder->name = name;

	folders.add(newFolder);

	if (activeFolder == NULL) activeFolder = newFolder;
	else activeFolder->folders.add(newFolder);

	if (folderNames.contains(name)) return false;
	folderNames.add(name);
	return true;
}

bool FileSystem::createFile(string name) {
	if (activeFolder == NULL) error("Active Folder does not selected.");

	File* newFile = new File;
	newFile->name = name;

	activeFolder->files.add(newFile);
	files.add(newFile);

	if (fileNames.contains(name)) return false;
	fileNames.add(name);
	return true;
}

FileSystem::Folder* FileSystem::getNewActiveFolder(string &name) {
	Queue<Folder*> q;
	q.enqueue(activeFolder);
	while (!q.isEmpty()) {
		Folder* temp = q.dequeue();
		if (temp->name == name && temp != activeFolder) return temp;
		foreach (Folder* folder in temp->folders)
			q.enqueue(folder);
	}
	return NULL;
}

bool FileSystem::selectFolder(string name) {
	if (activeFolder == NULL) error("Active Folder does not selected.");
	Folder* newActiveFolder = getNewActiveFolder(name);
	if (newActiveFolder == NULL) return false;
	activeFolder = newActiveFolder;
	return false;
}
