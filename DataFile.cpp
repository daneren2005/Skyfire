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
const char DataFile::STRING_IDENTIFIER = 0xB1;
const char DataFile::FLOAT_IDENTIFIER = 0xB2;

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
	fh.open(File::READ);
	while(!fh.eof())
	{
		// START
		fh.getCharacter();
		// console << fh.getCharacter() << newline;
		
		DataFile::Object* obj = new DataFile::Object();

		// Get size of this chunk
		int size = fh.getString(4).binaryTo<int, 4>();

		// Read each property
		String str = fh.getString(size);
		// console << str << " " << str.length() << " " << size << newline;
		for(long i = 0; i < str.length(); )
		{
			switch(str[i])
			{
				case STRING_IDENTIFIER:
				{
					int size1 = str[i + 1];
					int size2 = str[i + 2];
		
					String name = str.subStr(i + 3, size1);
					String value = str.subStr(i + 3 + size1, size2);
					if(name == "Name")
						obj->name = value;
					else
						obj->strings.insert(value, name);
					// console << name << "   " << value << " " << size1 + size2 + 3 << newline;
		
					i += size1 + size2 + 3;
					break;
				}
				case FLOAT_IDENTIFIER:
				{
					int size1 = str[i + 1];
					String name = str.subStr(i + 2, size1);
					String value = str.subStr(i + 2 + size1, 4);

					obj->floats.insert(value.binaryTo<float, 4>(), name);
					// console << name << "   " << value.binaryTo<float, 4>() << newline;
					i += 5;
					break;
				}
				default:
				{
					// Prevent infinite loop
					// console << "NO" << newline;
					i++;
					break;
				}
			}
		}
		
		this->insertObject(obj);
	}

	fh.close();
}
void DataFile::save()
{
	fh.open(File::BINARY_WRITE);
	for(Map<DataFile::Object*, String>::Iterator it = objects.begin(); !it; it++)
	{
		DataFile::Object* obj = it.value();

		Array<String> properties(obj->strings.size() + obj->floats.size() + obj->objects.size() + 1);
		uint size = 0;

		String prop = String(STRING_IDENTIFIER) + (uchar)4 + (uchar)obj->name.length() + String("Name") + obj->name;
		size += obj->name.length() + 7;
		properties.insert(prop);

		// Strings
		for(Map<String, String>::Iterator it2 = obj->strings.begin(); !it2; it2++)
		{
			prop = String(STRING_IDENTIFIER) + (uchar)it2.key().length() + (uchar)it2.value().length() + it2.key() + it2.value();
			size += it2.key().length() + it2.value().length() + 3;
			properties.insert(prop);
		}

		// Floats
		for(Map<float, String>::Iterator it2 = obj->floats.begin(); !it2; it2++)
		{
			prop = String(FLOAT_IDENTIFIER) + (uchar)it2.key().length() + it2.key() + toBinaryString<float, 4>(it2.value());
			size += it2.key().length() + 6;
			properties.insert(prop);
		}

		// Subobjects
		for(Map<DataFile::Object*, String>::Iterator it2 = obj->objects.begin(); !it2; it2++)
		{
			prop = String(STRING_IDENTIFIER) + (uchar)it2.key().length() + (uchar)it2.value()->name.length() + it2.key() + it2.value()->name;
			size += it2.key().length() + it2.value()->name.length() + 3;
			properties.insert(prop);
		}

		fh.writeCharacter(START);
		fh.writeString(toBinaryString<int, 4>(size));
		for(ulong i = 0; i < properties.size(); i++)
		{
			fh.writeString(properties[i]);
		}
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
	