#include "CString.h"
#include "Exceptions.h"
#include <string.h>

String::String()
{
	array = new char[1];
	array[0] = 0x0;
	this->size = 0;
}
String::String(const String& rhs)
{
	this->size = rhs.size;
	this->array = new char[size + 1];
	memcpy(this->array, rhs.array, size + 1);
}
String::String(const char* rhs)
{
	long i = 0;
	while(rhs[i] != NULL)
	{
		i++;
	}

	this->size = i;
	this->array = new char[this->size + 1];
	memcpy(this->array, rhs, this->size + 1);
}

String::~String()
{
	delete this->array;
}

char& String::operator[](unsigned pos)
{
	if(pos > this->size)
	{
		throw OutOfRange();
	}

	return this->array[pos];
}
const char& String::operator[](unsigned pos) const
{
	if(pos > this->size)
	{
		throw OutOfRange();
	}

	return this->array[pos];
}
String& String::operator+(const String& rhs)
{
	String* str = new String();
	str->size = this->size + rhs.size;
	str->array = new char[str->size + 1];
	memcpy(str->array, this->array, this->size);
	memcpy(str->array + this->size, rhs.array, rhs.size + 1);
	return *str;
}
String& String::operator+(const char* rhs)
{
	long i = 0;
	while(rhs[i] != 0x0)
	{
		i++;
	}

	String* str = new String();
	str->size = this->size + i;
	str->array = new char[str->size + 1];
	memcpy(str->array, this->array, this->size);
	memcpy(str->array + this->size, rhs, i + 1);

	return *str;
}
String& String::operator+(const char& rhs)
{
	String* str = new String();
	str->size = this->size + 1;
	str->array = new char[str->size + 1];
	memcpy(str->array, this->array, this->size);
	str->array[this->size] = rhs;
	str->array[this->size + 1] = NULL;

	return *str;
}
String& String::operator+=(const String& rhs)
{
	*this = *this + rhs;
	return *this;
}
String& String::operator+=(const char* rhs)
{
	*this = *this + rhs;
	return *this;
}
String& String::operator+=(const char& rhs)
{
	*this = *this + rhs;
	return *this;
}

String& String::operator=(const String& rhs)
{
	delete this->array;

	// Create new string
	this->size = rhs.size;
	this->array = new char[size + 1];
	memcpy(this->array, rhs.array, size + 1);

	return *this;
}
String& String::operator=(const char* rhs)
{
	delete this->array;

	long i = 0;
	while(rhs[i] != NULL)
	{
		i++;
	}

	this->size = i;
	this->array = new char[this->size + 1];
	memcpy(this->array, rhs, this->size + 1);

	return *this;
}

bool String::operator==(const String& rhs)
{
	if(this->size != rhs.size)
	{
		return false;
	}

	for(long i = 0; i < this->size; i++)
	{
		if(this->array[i] != rhs.array[i])
			return false;
	}

	return true;
}
bool String::operator==(const char* rhs)
{
	for(long i = 0; i < this->size; i++)
	{
		if(this->array[i] != rhs[i])
			return false;
	}

	return true;
}
bool String::operator!=(const String& rhs)
{
	if(this->size != rhs.size)
	{
		return true;
	}

	for(long i = 0; i < this->size; i++)
	{
		if(this->array[i] != rhs.array[i])
			return true;
	}

	return false;
}
bool String::operator!=(const char* rhs)
{
	for(long i = 0; i < this->size; i++)
	{
		if(this->array[i] != rhs[i])
			return true;
	}

	return false;
}

long String::length()
{
	return this->size;
}

const char* String::cStr()
{
	char* cString = new char[this->size];
	memcpy(cString, this->array, this->size + 1);
	return cString;
}

String String::subStr(long startPos)
{
	if(startPos >= this->size || startPos < 0)
	{
		throw OutOfRange();
	}

	String string;
	char* array = new char[this->size - startPos + 1];
	memcpy(array, this->array + startPos, this->size - startPos + 1);
	string.array = array;
	string.size = this->size - startPos;
	return string;
}
String String::subStr(long startPos, long length)
{
	if(startPos >= this->size || startPos < 0)
	{
		throw OutOfRange();
	}
	if(length <= 0)
	{
		return String();
	}

	// If length > till end of string just return rest of string
	if(length - startPos > this->size)
	{
		return this->subStr(startPos);
	}
	else
	{
		String string;
		char* array = new char[length + 1];
		memcpy(array, this->array + startPos, length);
		array[length] = 0x0;
		string.array = array;
		string.size = length;
		return string;
	}
}

Array<String> String::split(const String& delim)
{
	long pos1 = 0;
	long pos2 = 0;
	long count = 0;
	Array<String> list;
	for(long i = 0; i < this->size; i++)
	{
		for(long j = 0; this->array[i] == delim[j]; j++)
		{
			i++;
			if((j + 1) >= delim.size)
			{
				pos1 = pos2;
				pos2 = i;
				list[count] = this->subStr(pos1, pos2 - pos1 - delim.size);
				count++;

				if(j == 0)
				{
					i--;
				}
			}
		}
	}

	if(pos2 == 0)
	{
		list[count] = *this;
	}
	else
	{
		list[count] = this->subStr(pos2);
	}
	count++;

	list.resize(count);
	return list;
}
Array<String> String::split(const char* delim)
{
	long pos1 = 0;
	long pos2 = 0;
	long count = 0;
	Array<String> list;
	for(long i = 0; i < this->size; i++)
	{
		for(long j = 0; this->array[i] == delim[j]; j++)
		{
			i++;
			if(delim[j + 1] == 0x0)
			{
				pos1 = pos2;
				pos2 = i;
				list[count] = this->subStr(pos1, pos2 - pos1 - j - 1);
				count++;

				if(j == 0)
				{
					i--;
				}
			}
		}
	}

	if(pos2 == 0)
	{
		list[count] = *this;
	}
	else
	{
		list[count] = this->subStr(pos2);
	}
	count++;

	list.resize(count);
	return list;
}
Array<String> String::split(const char& delim)
{
	long pos1 = 0;
	long pos2 = -1;
	long count = 0;
	Array<String> list;
	for(long i = 0; i < this->size; i++)
	{
		if(this->array[i] == delim)
		{
			pos1 = pos2 + 1;
			pos2 = i;
			list[count] = this->subStr(pos1, pos2 - pos1);
			count++;
		}
	}

	if(pos2 == -1)
	{
		list[count] = *this;
	}
	else
	{
		list[count] = this->subStr(pos2);
	}
	count++;

	list.resize(count);
	return list;
}

long String::strPos(const String& search)
{
	// Go through every character in string and compare to delim
	for(long i = 0; i < this->size; i++)
	{
		for(long j = 0; this->array[i] == search[j]; j++)
		{
			i++;
			if((j + 1) >= search.size)
			{
				return i - search.size;
			}
		}
	}

	return -1;
}
long String::strPos(const char* search)
{
	// Go through every character in string and compare to delim
	for(long i = 0; i < this->size; i++)
	{
		for(long j = 0; this->array[i] == search[j]; j++)
		{
			i++;
			if(search[j + 1] == 0x0)
			{
				return i - j - 1;
			}
		}
	}

	return -1;
}
long String::strPos(const char& search)
{
	// Go through every character in string and compare to delim
	for(long i = 0; i < this->size; i++)
	{
		if(this->array[i] == search)
		{
			return i;
		}
	}

	return -1;
}
long String::strLastPos(const String& search)
{
	// Go through every character in string and compare to delim
	long lastPos = -1;
	for(long i = 0; i < this->size; i++)
	{
		for(long j = 0; this->array[i] == search[j]; j++)
		{
			i++;
			if((j + 1) >= search.size)
			{
				lastPos = i - search.size;
			}
		}
	}

	return lastPos;
}
long String::strLastPos(const char* search)
{
	// Go through every character in string and compare to delim
	long lastPos = -1;
	for(long i = 0; i < this->size; i++)
	{
		for(long j = 0; this->array[i] == search[j]; j++)
		{
			i++;
			if(search[j + 1] == 0x0)
			{
				lastPos = i - j - 1;
			}
		}
	}

	return lastPos;
}
long String::strLastPos(const char& search)
{
	// Go through every character in string and compare to delim
	long lastPos = -1;
	for(long i = 0; i < this->size; i++)
	{
		if(this->array[i] == search)
		{
			lastPos = i;
		}
	}

	return lastPos;
}
Array<long> String::strAllPos(const String& search)
{
	Array<long> list;
	long count = 0;
	for(long i = 0; i < this->size; i++)
	{
		for(long j = 0; this->array[i] == search[j]; j++)
		{
			i++;
			if((j + 1) >= search.size)
			{
				list[count] = i - search.size;
				count++;
			}
		}
	}
	return list;
}
Array<long> String::strAllPos(const char* search)
{
	// Go through every character in string and compare to delim
	Array<long> list;
	long count = 0;
	for(long i = 0; i < this->size; i++)
	{
		for(long j = 0; this->array[i] == search[j]; j++)
		{
			i++;
			if(search[j + 1] == 0x0)
			{
				list[count] = i - j - 1;
				count++;
			}
		}
	}

	return list;
}
Array<long> String::strAllPos(const char& search)
{
	// Go through every character in string and compare to delim
	Array<long> list;
	long count = 0;
	for(long i = 0; i < this->size; i++)
	{
		if(this->array[i] == search)
		{
			list[count] = i;
			count++;
		}
	}

	return list;
}

String& String::remove(const String& find)
{
	return *this;
}
String& String::remove(const char* find)
{
	return *this;
}
String& String::remove(const char& find)
{
	String* str = new String();
	long pos = 0;
	for(long i = 0; i < this->size; i++)
	{
		if(this->array[i] == find)
		{
			*str += this->subStr(pos, i - pos);
			pos = i + 1;
		}
	}

	if(pos < this->size)
	{
		*str += this->subStr(pos);
	}
	return *str;
}
String& String::remove(long startPos)
{
	return *this;
}
String& String::remove(long startPos, long length)
{
	return *this;
}
String& String::replace(const String& find, const String& replace)
{
	return *this;
}
String& String::replace(const char* find, const char* replace)
{
	return *this;
}
String& String::replace(const char& find, const char& replace)
{
	String* str = new String(*this);
	for(long i = 0; i < this->size; i++)
	{
		if(this->array[i] == find)
		{
			(*str)[i] = replace;
		}
	}

	return *str;
}
String& String::toLower()
{
	return *this;
}
String& String::toUpper()
{
	return *this;
}
