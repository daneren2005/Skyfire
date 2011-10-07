/*
	This file is part of Skyfire.

    Skyfire is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Skyfire is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Skyfire.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _FILE_H
#define	_FILE_H

#include "Date.h"
#include "Exceptions.h"
#include "CString.h"
#include "SharedPointer.h"

class Folder;

/*
	TODO
	
	Binary will be a major problem in this implementation.
	The whole buffer format that is currently being used will
	not work for binary files because of the fact that it will
	be looking for newline characters and comparing the current pos
	with them which will cause unknown behaviour.  Time to test!

	Possible solution: TextFile and BinaryFile classes with a base
	class File that only implements basic stuff that is true for all
	files.

	Also possible to give entirely different behaviour/return a different
	instance based on what the user passes in for the mode.  IE if 
	the user passes in without binary it will return this, overwise
	it will return a overloaded Binary class that has different behaviour
	defined for it that is more inline with a binary file.  Only problem
	would be that if the user used getLine with a binary file what would
	the behaviour be?

	Also need to Bad FileException that other File Exceptions inherit
	from so that way you could catch for FileException instead of being
	limited to only using Exception or the specifying the individual
	File Exception classes.
*/

class File
{
public:
	File();
	#ifdef WIN32
		File(const String& filename, const String& delim = "\r\n");
		File(const char* filename, const char* delim = "\r\n");
	#endif
	#ifdef __linux__
		File(const String& filename, const String& delim = '\n');
		File(const char* filename, const char* delim = "\n");
	#endif
	File(const File& orig);
	virtual ~File();

	void open(int mode = READ);
	void close();
	bool isOpen();
	bool eof();

	String getFileName() const;		// model1
	String getFileType() const;		// obj
	String getFullName() const;		// model1.obj
	String getParentPath() const;	// data/model1/
	String getFullPath() const;		// data/model1/model1.obj
	Folder getParentFolder() const;

	bool canRead() const;
	bool canWrite() const;
	bool canExecute() const;
	int getPermissions() const;
	int getOwnerPermissions() const;
	int getGroupPermissions() const;
	int getOtherPermissions() const;
	// String getOwner() const;
	int getOwnerID() const;
	// String getGroup() const;
	int getGroupID() const;
	bool doesExist() const;

	// bool setPermissions(int mode);
	// bool setOwnerPermissions(int mode);
	// bool setGroupPermissions(int mode);
	// bool setOtherPermissions(int mode);
	// bool setOwner(int id);
	// bool setGroup(int id);

	// Get the size of the file
	long getSize() const;
	double getSizeKB() const;
	double getSizeMB() const;
	double getSizeGB() const;
	// Get the actual size of file (multiple of filesystem block size)
	long getPhysicalSize() const;
	double getPhysicalSizeKB() const;
	double getPhysicalSizeMB() const;
	double getPhysicalSizeGB() const;

	Date getLastAccessed() const;
	Date getLastModified() const;

	char getCharacter();
	char peekCharacter();
	String getString(int num);
	String peekString(int num);
	String getLine();
	String peekLine();

	void writeCharacter(const char& c);
	void writeString(const String& str);
	void writeString(const char* str);
	void writeLine(const String& str);
	void writeLine(const char* str);

	File& operator<<(const String& rhs);
	File& operator<<(const char* rhs);
	File& operator>>(String& rhs);
	File& operator>>(char* rhs);

	File& operator=(const File& rhs);
	bool operator==(const File& rhs);
	bool operator!=(const File& rhs);
protected:
	struct BUFFER
	{
		String delim;
		String buffer;
		Array<long> positions;
		ulong oldPos;
		ulong i;
		bool bufferEmpty;
	};
	
	virtual void checkFillBuffer();

	String filename;	
	SharedPointer<FILE*> handle;
	SharedPointer<BUFFER> buffer;

	const static int MODE_READ = 1;
	const static int MODE_WRITE = 2;
	const static int MODE_APPEND = 4;
	const static int MODE_TRUNCATE = 8;
	const static int MODE_BINARY = 16;
	
	const static int CHAR_SIZE = 1;
	const static int BUFFER_SIZE = 16384;

public:
	// Open a file pointer at head
	const static int READ = MODE_READ;
	// Create or open w/ truncate pointer at head
	const static int WRITE = MODE_WRITE | MODE_TRUNCATE;
	// open for writing append at end
	const static int WRITE_APPEND = MODE_WRITE | MODE_APPEND;
	// open for read/writing pointer at head
	const static int READ_WRITE_HEAD = MODE_READ | MODE_WRITE;
	// Open for reading/writing append at end
	const static int READ_WRITE_APPEND = MODE_READ | MODE_WRITE | MODE_APPEND;
	// Open for reading/writing, create or open w/ truncate pointer at head
	const static int READ_WRITE_TRUNCATE = MODE_READ | MODE_WRITE | MODE_TRUNCATE;

	// Open a file pointer at head
	const static int BINARY_READ = MODE_READ | MODE_BINARY;
	// Create or open w/ truncate pointer at head
	const static int BINARY_WRITE = MODE_WRITE | MODE_TRUNCATE | MODE_BINARY;
	// open for writing append at end
	const static int BINARY_WRITE_APPEND = MODE_WRITE | MODE_APPEND | MODE_BINARY;
	// open for read/writing pointer at head
	const static int BINARY_READ_WRITE_HEAD = MODE_READ | MODE_WRITE | MODE_BINARY;
	// Open for reading/writing append at end
	const static int BINARY_READ_WRITE_APPEND = MODE_READ | MODE_WRITE | MODE_APPEND | MODE_BINARY;
	// Open for reading/writing, create or open w/ truncate pointer at head
	const static int BINARY_READ_WRITE_TRUNCATE = MODE_READ | MODE_WRITE | MODE_TRUNCATE | MODE_BINARY;
};

class FileException : public Exception
{
public:
	FileException(String filename)
	{
		this->fileName = filename;
	}

	String fileName;
};

class InvalidFileMode : public FileException
{
public:
	InvalidFileMode(String fileName, String mode) : FileException(fileName)
	{
		this->msg = String("Exception: invalid file opening mode: ") + String(mode);
	}
};
class InvalidFilePermissions : public FileException
{
public:
	InvalidFilePermissions(String fileName) : FileException(fileName)
	{
		this->msg = String("Exception: Invalid file permissions: ") + fileName;
	}
};
class InvalidFile : public FileException
{
public:
	InvalidFile(String fileName) : FileException(fileName)
	{
		this->msg = String("Exception: Invalid file name: ") + fileName;
	}
};
class FileNotOpen : public FileException
{
public:
	FileNotOpen(String fileName) : FileException(fileName)
	{
		this->msg = String("Exception: File is not open: ") + fileName;
	}
};

#endif	/* _FILE_H */
