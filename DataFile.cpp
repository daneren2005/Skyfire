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
#include "BasicList.h"

const char DataFile::START = 0xB0;
const char DataFile::END = 0xB1;
const char DataFile::SEPARATOR = 0xB3;
const char DataFile::STRING_IDENTIFIER = 0xB4;

DataFile::DataFile(const String& filename)
{
	this->fh = File(filename, END);
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
	fh.open(File::READ);
	BasicList<Object*> stack;
	Object* current = 0x0;
	while(!fh.eof())
	{
		String line = fh.getLine();
		Array<long> ids = line.strAllPos(STRING_IDENTIFIER);
		long j = 0;
		Array<long> seps = line.strAllPos(SEPARATOR);
		long k = 0;
		
		// Go through each part of the line
		for(long i = 0; i < line.length(); i++)
		{
			switch(line[i])
			{
				case START:
				{
					if(current != 0x0)
						stack.pushBack(current);
					current = new Object();
					break;
				}
				case STRING_IDENTIFIER:
				{
					// Increment i past id
					i++;
					
					// Get the j = next id
					j++;
					long end = ids[j];
					j++;
					
					// Get separator
					long middle = seps[k];
					k++;
					
					// Get values and insert them in
					String name = line.subStr(i, middle - i);
					String value = line.subStr(middle + 1, end - middle - 1);
					if(name == "Name")
						current->name = value;
					else
						current->properties.insert(value, name);
					
					i = end;
					break;
				}
			}
		}
		
		if(stack.size() > 0)
		{
			stack.back()->objects.insert(current, current->name);
			current = stack.popBack();
		}
		else
		{
			this->insertObject(current);
			current = 0x0;
		}
	}
}
void DataFile::save()
{
	fh.open(File::WRITE);
	for(Map<DataFile::Object*, String>::Iterator it = objects.begin(); !it; it++)
	{
		fh.writeCharacter(START);
		fh.writeCharacter(STRING_IDENTIFIER);
		fh.writeString("Name");
		fh.writeCharacter(SEPARATOR);
		fh.writeString(it.key());
		fh.writeCharacter(STRING_IDENTIFIER);
		
		for(Map<String, String>::Iterator prop = it.value()->properties.begin(); !prop; prop++)
		{
			fh.writeCharacter(STRING_IDENTIFIER);
			fh.writeString(prop.key());
			fh.writeCharacter(SEPARATOR);
			fh.writeString(prop.value());
			fh.writeCharacter(STRING_IDENTIFIER);
		}
		
		fh.writeCharacter(END);
	}
	fh.close();
}

void DataFile::insertObject(DataFile::Object* obj)
{
	objects.insert(obj, obj->name);
}
void DataFile::updateObject(DataFile::Object* obj)
{
	objects.remove(obj->name);
	objects.insert(obj, obj->name);
}
DataFile::Object* DataFile::getObject(const String& name)
{
	return objects.search(name);
}
void DataFile::removeObject(const String& name)
{
	objects.remove(name);
}

Map<DataFile::Object*, String>::Iterator DataFile::begin()
{
	return objects.begin();
}
	