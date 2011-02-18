/* 
 * File:   File.h
 * Author: scott
 *
 * Created on February 8, 2011, 12:11 PM
 */

#ifndef _FILE_H
#define	_FILE_H

#include "CString.h"
#include <fstream>

class File
{
public:
	File(const char* filename);
	File(const String& filename);
	File(const File& orig);
	virtual ~File();

	void open();
	void close();
	bool isOpen();
	bool eof();

	String fileName();	// model1
	String fileType();	// obj
	String fullName();	// model1.obj
	String filePath();	// data/model1/
	String fullPath();	// data/model1/model1.obj

	char getCharacter();
	char peekCharacter();
	String getLine();
private:
	String filename;
	std::ifstream handler;
};

#endif	/* _FILE_H */

