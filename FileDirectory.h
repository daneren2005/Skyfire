/* 
 * File:   FileDirectory.h
 * Author: scott
 *
 * Created on February 17, 2011, 1:46 PM
 */

#ifndef _FILEDIRECTORY_H
#define	_FILEDIRECTORY_H

#include "File.h"

class FileDirectory
{
public:
	FileDirectory();
	FileDirectory(const FileDirectory& orig);
	virtual ~FileDirectory();

	File getFile(String filename);
	void changeDir(String dir);
private:
	String currDir;
};

#endif	/* _FILEDIRECTORY_H */

