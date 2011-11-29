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

#include "DataFile.h"

const char DataFile::BLOCK_BRACKET = 0xB0;
const char DataFile::OBJECT_BRACKET = 0xB1;
const char DataFile::PROPERTY_BRACKET = 0xB2;
const char DataFile::SEPARATOR = 0xB3;
const char DataFile::IDENTIFIER = 0xB4;

DataFile::DataFile(const String& filename)
{
	this->fh = File(filename);
}
DataFile::DataFile(const File& fh)
{
	this->fh = fh;
}

DataFile::DataFile(const DataFile& orig)
{
	this->fh = orig.fh;
}

DataFile::~DataFile()
{
	
}

void DataFile::load()
{
	
}
void DataFile::save()
{
	fh.open(File::WRITE);
	for(Map<DataFile::Object, String>::Iterator it = objects.begin(); !it; it++)
	{
		fh.writeCharacter(OBJECT_BRACKET);
		
		fh.writeCharacter(IDENTIFIER);
		fh.writeString("Name");
		fh.writeCharacter(IDENTIFIER);
		fh.writeCharacter(IDENTIFIER);
		fh.writeString(it.key());
		fh.writeCharacter(IDENTIFIER);
		
		for(Map<String, String>::Iterator prop = it.value().properties.begin(); !prop; prop++)
		{
			fh.writeCharacter(SEPARATOR);
			fh.writeCharacter(IDENTIFIER);
			fh.writeString(prop.key());
			fh.writeCharacter(IDENTIFIER);
			fh.writeCharacter(IDENTIFIER);
			fh.writeString(prop.value());
			fh.writeCharacter(IDENTIFIER);
		}
		
		fh.writeCharacter(OBJECT_BRACKET);
	}
	fh.close();
}

void DataFile::insertObject(const DataFile::Object& obj)
{
	objects.insert(obj, obj.name);
}
DataFile::Object DataFile::getObject(const String& name)
{
	return objects.search(name);
}
void DataFile::updateObject(const DataFile::Object& obj)
{
	objects.remove(obj.name);
	objects.insert(obj, obj.name);
}
void DataFile::removeObject(const String& name)
{
	objects.remove(name);
}
	