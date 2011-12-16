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

#include "File.h"
#include "Folder.h"
#include <sstream>
#include <sys/stat.h>
#include <cstdio>
#include <string.h>


File::File()
{
	// TODO: Get programs current working directory
	this->filename = "/";
	this->handle = 0x0;
	this->buffer = 0x0;
}
File::File(const String& filename, const String& delim)
{
	#ifdef WIN32
		if(filename[1] == ':')
			this->filename = filename;
	#endif
	#ifdef __linux__
		if(filename[0] == '/')
			this->filename = filename;
	#endif
	else
		this->filename = Folder::getCWD() + "/" + filename;
	
	this->handle = new FILE*;
	*this->handle = 0x0;
	this->buffer = new BUFFER;
	this->buffer->delim = delim;
}
File::File(const char* filename, const char* delim)
{
	#ifdef WIN32
		if(filename[1] == ':')
			this->filename = filename;
	#endif
	#ifdef __linux__
		if(filename[0] == '/')
			this->filename = filename;
	#endif
	else
		this->filename = Folder::getCWD() + "/" + String(filename);
	this->handle = new FILE*;

	this->handle = new FILE*;
	*this->handle = 0x0;
	this->buffer = new BUFFER;
	this->buffer->delim = delim;
}
File::File(const File& orig)
{
	this->filename = orig.filename;
	this->handle = orig.handle;
	this->buffer = orig.buffer;
}

File::~File()
{	
	if(*this->handle != 0x0)
	{
		// fclose(*this->handle);
	}
}

void File::open(int mode)
{
	switch(mode)
	{
		case READ:
			*handle = fopen(filename.cStr(), "rt");
			break;
		case WRITE:
			*handle = fopen(filename.cStr(), "wt");
			break;
		case READ_WRITE_HEAD:
			*handle = fopen(filename.cStr(), "r+t");
			break;
		case WRITE_APPEND:
			*handle = fopen(filename.cStr(), "at");
			break;
		case READ_WRITE_APPEND:
			*handle = fopen(filename.cStr(), "a+t");
			break;
		case READ_WRITE_TRUNCATE:
			*handle = fopen(filename.cStr(), "w+t");
			break;
		case BINARY_READ:
			*handle = fopen(filename.cStr(), "rb");
			break;
		case BINARY_WRITE:
			*handle = fopen(filename.cStr(), "wb");
			break;
		case BINARY_READ_WRITE_HEAD:
			*handle = fopen(filename.cStr(), "r+b");
			break;
		case BINARY_WRITE_APPEND:
			*handle = fopen(filename.cStr(), "ab");
			break;
		case BINARY_READ_WRITE_APPEND:
			*handle = fopen(filename.cStr(), "a+b");
			break;
		case BINARY_READ_WRITE_TRUNCATE:
			*handle = fopen(filename.cStr(), "w+b");
			break;
		default:
			throw InvalidFileMode(filename, mode);
			break;
	}

	buffer->bufferEmpty = true;
}
void File::close()
{
	if(*this->handle != 0x0)
	{
		fclose(*handle);
		*handle = 0x0;
	}
}
bool File::isOpen()
{
	return *handle != 0x0;
}
bool File::eof()
{
	if(buffer->i < buffer->positions.size() && buffer->positions.size() != 0)
	{
		return false;
	}
	else
	{
		if(!buffer->bufferEmpty)
			return false;
		else
			return feof(*handle);
	}
}

String File::getFileName() const
{
	int start = filename.strLastPos('/');
	int end = filename.strLastPos('.');
	if(end == String::npos)
	{
		return filename.subStr(start + 1);
	}
	else
	{
		return filename.subStr(start + 1, end - start - 1);
	}
}
String File::getFileType() const
{
	int start = filename.strLastPos('.');
	if(start == String::npos)
	{
		return "";
	}
	else
	{
		return filename.subStr(start + 1);
	}
}
String File::getFullName() const
{
	int start = filename.strLastPos('/');
	return filename.subStr(start + 1);
}
String File::getParentPath() const
{
	int end = filename.strLastPos('/');
	return filename.subStr(0, end + 1);
}
String File::getFullPath() const
{
	return filename;
}

Folder File::getParentFolder() const
{
	long pos = filename.strLastPos("/");
	return Folder(filename.subStr(0, pos));
}

bool File::canRead() const
{
	#ifdef WIN32
		// TODO: fill out
		return false;
	#endif
	#ifdef __linux__
		return access(filename.cStr(), R_OK) == 0;
	#endif
}
bool File::canWrite() const
{
	#ifdef WIN32
		// TODO: fill out
		return false;
	#endif
	#ifdef __linux__
		return access(filename.cStr(), W_OK) == 0;
	#endif
}
bool File::canExecute() const
{
	#ifdef WIN32
		// TODO: fill out
		return false;
	#endif
	#ifdef __linux__
		return access(filename.cStr(), X_OK) == 0;
	#endif
}

int File::getPermissions() const
{
	#ifdef WIN32
		// TODO: fill out
		return 0;
	#endif
	#ifdef __linux__
		struct stat statBuffer;
		if(stat(filename.cStr(), &statBuffer) != 0)
			return 0;
	
		return ((statBuffer.st_mode & S_IRWXU) >> 6) * 100 + ((statBuffer.st_mode & S_IRWXG) >> 3) * 10 + (statBuffer.st_mode & S_IRWXO);
	#endif
}
int File::getOwnerPermissions() const
{
	#ifdef WIN32
		// TODO: fill out
		return 0;
	#endif
	#ifdef __linux__
		struct stat statBuffer;
		if(stat(filename.cStr(), &statBuffer) != 0)
			return 0;
	
		return (statBuffer.st_mode & S_IRWXU) >> 6;
	#endif
}
int File::getGroupPermissions() const
{
	#ifdef WIN32
		// TODO: fill out
		return 0;
	#endif
	#ifdef __linux__
		struct stat statBuffer;
		if(stat(filename.cStr(), &statBuffer) != 0)
			return 0;
	
		return (statBuffer.st_mode & S_IRWXG) >> 3;
	#endif
}
int File::getOtherPermissions() const
{
	#ifdef WIN32
		// TODO: fill out
		return 0;
	#endif
	#ifdef __linux__
		struct stat statBuffer;
		if(stat(filename.cStr(), &statBuffer) != 0)
			return 0;
	
		return statBuffer.st_mode & S_IRWXO;
	#endif
}
int File::getOwnerID() const
{
	#ifdef WIN32
		// TODO: fill out
		return 0;
	#endif
	#ifdef __linux__
		struct stat statBuffer;
		if(stat(filename.cStr(), &statBuffer) != 0)
			return 0;
	
		return statBuffer.st_uid;
	#endif
}
int File::getGroupID() const
{
	#ifdef WIN32
		// TODO: fill out
		return 0;
	#endif
	#ifdef __linux__
		struct stat statBuffer;
		if(stat(filename.cStr(), &statBuffer) != 0)
			return 0;
	
		return statBuffer.st_gid;
	#endif
}

bool File::doesExist() const
{
	#ifdef WIN32
		// TODO: fill out
		return false;
	#endif
	#ifdef __linux__
		return access(filename.cStr(), F_OK) == 0;
	#endif
}

long File::getSize() const
{
	#ifdef WIN32
		// TODO: fill out
		return 0;
	#endif
	#ifdef __linux__
		struct stat statBuffer;
		if(stat(filename.cStr(), &statBuffer) != 0)
			return 0;
	
		return statBuffer.st_size;
	#endif
}
double File::getSizeKB() const
{
	return this->getSize() / 1024.0;
}
double File::getSizeMB() const
{
	return this->getSize() / 1048576.0;
}
double File::getSizeGB() const
{
	return this->getSize() / 1073741824.0;
}

long File::getPhysicalSize() const
{
	#ifdef WIN32
		// TODO: fill out
		return 0;
	#endif
	#ifdef __linux__
		struct stat statBuffer;
		if(stat(filename.cStr(), &statBuffer) != 0)
			return 0;
	
		int blocks = statBuffer.st_size / statBuffer.st_blksize;
		if(statBuffer.st_size % statBuffer.st_blksize != 0)
			blocks++;
	
		return statBuffer.st_blksize * blocks;
	#endif
}
double File::getPhysicalSizeKB() const
{
	return this->getPhysicalSize() / 1024.0;
}
double File::getPhysicalSizeMB() const
{
	return this->getPhysicalSize() / 1048576.0;
}
double File::getPhysicalSizeGB() const
{
	return this->getPhysicalSize() / 1073741824.0;
}

Date File::getLastAccessed() const
{
	#ifdef WIN32
		// TODO: fill out
		return Date();
	#endif
	#ifdef __linux__
		struct stat statBuffer;
		stat(filename.cStr(), &statBuffer);
	
		return Date(statBuffer.st_atime);
	#endif
}
Date File::getLastModified() const
{
	#ifdef WIN32
		// TODO: fill out
		return Date();
	#endif
	#ifdef __linux__
		struct stat statBuffer;
		stat(filename.cStr(), &statBuffer);
	
		return Date(statBuffer.st_mtime);
	#endif
}

char File::getCharacter()
{
	checkFillBuffer();

	char value = buffer->buffer[buffer->oldPos];

	buffer->oldPos++;
	if(buffer->oldPos == buffer->positions[buffer->i])
	{
		buffer->i++;

		if(buffer->i == buffer->positions.size())
		{
			buffer->bufferEmpty = true;
		}
	}

	return value;
}
char File::peekCharacter()
{
	checkFillBuffer();

	return buffer->buffer[buffer->oldPos];
}

String File::getString(int num)
{
	checkFillBuffer();

	ulong pos = buffer->oldPos;
	buffer->oldPos+= num;

	String oldBuffer;
	while(buffer->oldPos >= buffer->positions[buffer->i])
	{
		// Skip to next char if oldPos = newline character
		if(buffer->oldPos == buffer->positions[buffer->i])
			buffer->oldPos++;

		buffer->i++;

		// Check integrity of buffer
		if(buffer->i == buffer->positions.size())
		{
			buffer->bufferEmpty = true;
		}
		// Need to get data that is in next buffer
		else if(buffer->i > buffer->positions.size())
		{
			oldBuffer = buffer->buffer.subStr(pos);
			ulong temp = buffer->buffer.length() - pos;
	
			buffer->bufferEmpty = true;
			checkFillBuffer();

			buffer->oldPos = temp;
			num = temp;
			pos = 0;
		}
	}

	return oldBuffer + buffer->buffer.subStr(pos, num);
}
String File::peekString(int num)
{
	checkFillBuffer();
	return buffer->buffer.subStr(buffer->oldPos, num);
}

String File::getLine()
{
	checkFillBuffer();

	ulong pos;
	if(buffer->i != buffer->positions.size())
	{	
		pos = buffer->positions[buffer->i];
	}
	else
	{
		pos = buffer->buffer.length() + 1;
	}

	buffer->i++;
	if(buffer->i >= buffer->positions.size())
	{
		// Make sure not just at end of file
		if(buffer->buffer.length() == File::BUFFER_SIZE)
		{
			buffer->bufferEmpty = true;
		}
		// Check if nothing past the last newline
		else if(buffer->i == buffer->positions.size() && buffer->positions[buffer->i - 1] + buffer->delim.length() == buffer->buffer.length())
		{
			buffer->bufferEmpty = true;
		}
		// Check if already got what was past the last newline
		else if(buffer->i > buffer->positions.size())
		{
			buffer->bufferEmpty = true;
		}
	}
	String line;
	line = buffer->buffer.subStr(buffer->oldPos, pos - buffer->oldPos);
	buffer->oldPos = pos + buffer->delim.length();
	return line;
}
String File::peekLine()
{
	checkFillBuffer();
	
	ulong pos = buffer->positions[buffer->i];
	
	return buffer->buffer.subStr(buffer->oldPos, pos - buffer->oldPos);
}

void File::writeCharacter(const char& c)
{
	if(!isOpen())
		throw FileNotOpen(filename);

	fputc((int)c, *handle);
}
void File::writeString(const String& str)
{
	if(!isOpen())
		throw FileNotOpen(filename);

	fwrite(str.cStr(), 1, str.length(), *handle);
}
void File::writeString(const char* str)
{
	if(!isOpen())
		throw FileNotOpen(filename);

	fputs(str, *handle);
}
void File::writeLine(const String& str)
{
	if(!isOpen())
		throw FileNotOpen(filename);

	fwrite(str.cStr(), 1, str.length(), *handle);
	fputs(buffer->delim.cStr(), *handle);
}
void File::writeLine(const char* str)
{
	if(!isOpen())
		throw FileNotOpen(filename);

	fputs(str, *handle);
	fputs(buffer->delim.cStr(), *handle);
}

File& File::operator<<(const String& rhs)
{
	this->writeLine(rhs);
	return *this;
}
File& File::operator<<(const char* rhs)
{
	this->writeLine(rhs);
	return *this;
}
File& File::operator>>(String& rhs)
{
	rhs = this->getLine();
	return *this;
}
File& File::operator>>(char* rhs)
{
	String str = this->getLine();
	memcpy(rhs, str.cStr(), str.length() + 1);
	return *this;
}

File& File::operator=(const File& rhs)
{
	this->filename = rhs.filename;
	this->handle = rhs.handle;
	this->buffer = rhs.buffer;
	return *this;
}
bool File::operator==(const File& rhs)
{
	return this->handle == rhs.handle;
}
bool File::operator!=(const File& rhs)
{
	return this->handle != rhs.handle;
}

void File::checkFillBuffer()
{
	if(*handle == 0x0)
		throw FileNotOpen(this->filename);

	if(buffer->bufferEmpty == true)
	{
		// Need to rewind to last \n so not losing data
		if(buffer->positions.size() != 0)
		{
			long pos = buffer->positions[buffer->i - 1];
			long end = buffer->buffer.length();
			fseek(*handle, pos - end + 1, SEEK_CUR);
		}
		
		char* buff = new char[BUFFER_SIZE + 1];
		long read = fread(buff, CHAR_SIZE, BUFFER_SIZE, *handle);
		buffer->buffer = String(buff, read);
		delete[] buff;
		buffer->positions = buffer->buffer.strAllPos(buffer->delim);
		buffer->i = 0;
		buffer->oldPos = 0;
		
		if(buffer->positions.size() == 0)
			buffer->positions.insert(buffer->buffer.length());
		
		buffer->bufferEmpty = false;
	}
}