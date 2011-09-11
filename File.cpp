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

int File::CHAR_SIZE = 1;
int File::BUFFER_SIZE = 16384; // 32768;

File::File(const char* filename)
{
	this->filename = String(filename);
	this->handle = 0x0;
}
File::File(const String& filename)
{
	this->filename = filename;
	this->handle = 0x0;
}
File::File(const File& orig)
{
	this->filename = orig.filename;
	this->handle = orig.handle;
}

File::~File()
{
	/*if(this->handler.is_open())
		this->handler.close();*/
	
	if(this->handle != 0x0)
	{
		fclose(this->handle);
	}
}

void File::open()
{
	/*this->handler.open(this->filename.cStr());

	if(!this->handler.good())
	{
		console << "File::open error: Failed to open file " << filename << newline;
	}*/
	
	this->handle = fopen(this->filename.cStr(), "r");
	bufferEmpty = true;
}
void File::close()
{
	/*if(this->handler.is_open())
		this->handler.close();*/
	
	fclose(this->handle);
	this->handle = 0x0;
}
bool File::isOpen()
{
	// return this->handler.is_open();
	return this->handle != 0x0;
}
bool File::eof()
{
	if(i != positions.size())
		return false;
	else
		return feof(handle);
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
	/*char temp;
	handler.get(temp);
	return temp;*/
	
	return fgetc(handle);
}
char File::peekCharacter()
{
	// return handler.peek();
	
	char temp = fgetc(handle);
	fseek(handle, -1, SEEK_CUR);
	return temp;
}
String File::getLine()
{
	/*std::string temp;
	getline(this->handler, temp);
	return String(temp.c_str(), temp.length());*/
	
	if(bufferEmpty == true)
	{
		// Need to rewind to last \n so not losing data
		if(positions.size() != 0)
		{
			long pos = positions[i - 1];
			long end = buffer.length();
			fseek(handle, pos - end, SEEK_CUR);
		}
		
		char* buff = new char[BUFFER_SIZE + 1];
		long read = fread(buff, CHAR_SIZE, BUFFER_SIZE, handle);
		buffer = String(buff, read - 1);
		delete[] buff;
		positions = buffer.strAllPos('\n');
		i = 0;
		oldPos = 0;
		
		bufferEmpty = false;
	}
	
	long pos = positions[i];
	i++;
	if(i == positions.size())
	{
		bufferEmpty = true;
	}
	
	String line;
    if(buffer[pos - 1] == '\r')
    { 
            line = buffer.subStr(oldPos, pos - oldPos - 1);
    }
    else
    {
            line = buffer.subStr(oldPos, pos - oldPos);
    }

    oldPos = pos + 1;
    return line;
}
