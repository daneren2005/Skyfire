/* 
 * File:   File.cpp
 * Author: scott
 * 
 * Created on February 8, 2011, 12:11 PM
 */

#include "File.h"
#include "Console.h"
#include <iostream>
#include <sstream>

File::File(const char* filename)
{
	this->filename = String(filename);
}
File::File(const String& filename)
{
	this->filename = filename;
}
File::File(const File& orig)
{
	this->filename = orig.filename;
}

File::~File()
{
	this->handler.close();
}

void File::open()
{
	this->handler.open(this->filename.cStr());

	if(!this->handler.good())
	{
		console << "File::open error: Failed to open file " << filename << newline;
	}
}
void File::close()
{
	this->handler.close();
}
bool File::isOpen()
{
	return this->handler.is_open();
}
bool File::eof()
{
	return !this->handler.good();
}

String File::fileName()
{
	int start = this->filename.strLastPos('/');
	int end = this->filename.strLastPos('.');
	if(end == String::npos)
	{
		return filename.subStr(start + 1);
	}
	else
	{
		return filename.subStr(start + 1, end - start - 1);
	}
}
String File::fileType()
{
	int start = this->filename.strLastPos('.');
	if(start == String::npos)
	{
		return "";
	}
	else
	{
		return filename.subStr(start + 1);
	}
}
String File::fullName()
{
	int start = this->filename.strLastPos('/');
	return filename.subStr(start + 1);
}
String File::filePath()
{
	int end = this->filename.strLastPos('/');
	return filename.subStr(0, end + 1);
}
String File::fullPath()
{
	return filename;
}

char File::getCharacter()
{
	char temp;
	handler.get(temp);
	return temp;
}
char File::peekCharacter()
{
	return handler.peek();
}
String File::getLine()
{
	std::string temp;
	getline(this->handler, temp);
	String line(temp.c_str());
	return line;
}
