/* 
 * File:   FileDirectory.cpp
 * Author: scott
 * 
 * Created on February 17, 2011, 1:46 PM
 */

#include "FileDirectory.h"

FileDirectory::FileDirectory()
{
	this->currDir = String();
}

FileDirectory::FileDirectory(const FileDirectory& orig)
{
	this->currDir = orig.currDir;
}

FileDirectory::~FileDirectory()
{
}

File FileDirectory::getFile(String filename)
{
	return File(currDir + filename);
}
void FileDirectory::changeDir(String dir)
{
	this->currDir = this->currDir + "/" + dir;
}
