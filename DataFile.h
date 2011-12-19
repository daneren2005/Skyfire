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

#ifndef _DATA_FILE_H
#define	_DATA_FILE_H

#include "File.h"
#include "Map.h"
#include "List.h"

class DataFile
{
public:
	static const char START;
	static const char STRING_IDENTIFIER;
	static const char FLOAT_IDENTIFIER;
	
	DataFile(const String& filename);
	DataFile(const File& fh);
	DataFile(const DataFile& orig);
	virtual ~DataFile();
	
	void load();
	void save();
	
	class Property;
	class Object;
	
	void insertObject(DataFile::Object* obj);
	void updateObject(DataFile::Object* obj);
	Object* getObject(const String& name);
	void removeObject(const String& name);
	
	Map<Object*, String>::Iterator begin();
private:
	File fh;
	Map<DataFile::Object*, String> objects;
};

class DataFile::Object
{
public:
	Object(){}
	Object(String name) : name(name) {}
	Object(const Object& orig) : name(orig.name), strings(orig.strings), floats(orig.floats), objects(orig.objects) {}
	
	String name;
	Map<String, String> strings;
	Map<float, String> floats;
	Map<DataFile::Object*, String> objects;
};

#endif	/* DATAFILE_H */

