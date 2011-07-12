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
	
	FILE* handle;
	
	String buffer;
	Array<long> positions;
	long oldPos;
	long i;
	bool bufferEmpty;
	
	static int CHAR_SIZE;
	static int BUFFER_SIZE;
};

#endif	/* _FILE_H */

