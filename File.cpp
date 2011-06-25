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
	if(this->handler.is_open())
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
	if(this->handler.is_open())
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
	return String(temp.c_str(), temp.length());
}
