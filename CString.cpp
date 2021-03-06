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
	while(rhs[i] != 0x0)
	{
		i++;
	}

	this->size = i;
	this->array = new char[this->size + 1];
	memcpy(this->array, rhs, this->size + 1);
}
String::String(const char* rhs, long size)
{
	this->size = size;
	this->array = new char[size + 1];
	memcpy(this->array, rhs, size);
	this->array[size] = 0x0;
}
String::String(char rhs)
{
	this->size = 1;
	this->array = new char[2];
	this->array[0] = rhs;
	this->array[1] = 0x0;
}
String::String(int rhs)
{
	const int DIFF = '0' - 0;

	int neg = 0;
	if(rhs < 0)
	{
		neg = 1;
		rhs = -rhs;
	}

	Array<char> buffer(8);
	if(rhs != 0)
	{
		while(rhs > 0)
		{
			buffer.insert(rhs % 10);
			rhs = rhs / 10;
		}
	}
	else
	{
		buffer.insert(0);
	}

	this->size = buffer.size();
	this->array = new char[buffer.size() + 1 + neg];
	for(int j = 0; j < buffer.size(); j++)
	{
		this->array[j + neg] = buffer[buffer.size() - j - 1] + DIFF;
	}

	if(neg == 1)
	{
		this->array[0] = '-';
	}

	this->array[buffer.size() + neg] = 0x0;
}
String::String(long rhs)
{
	const int DIFF = '0' - 0;

	int neg = 0;
	if(rhs < 0)
	{
		neg = 1;
		rhs = -rhs;
	}

	Array<char> buffer(8);
	if(rhs != 0)
	{
		while(rhs > 0)
		{
			buffer.insert(rhs % 10);
			rhs = rhs / 10;
		}
	}
	else
	{
		buffer.insert(0);
	}

	this->size = buffer.size();
	this->array = new char[buffer.size() + 1 + neg];
	for(int j = 0; j < buffer.size(); j++)
	{
		this->array[j + neg] = buffer[buffer.size() - j - 1] + DIFF;
	}

	if(neg == 1)
	{
		this->array[0] = '-';
	}

	this->array[buffer.size() + neg] = 0x0;
}
String::String(float rhs)
{
	const int DIFF = '0' - 0;

	int neg = 0;
	if(rhs < 0)
	{
		neg = 1;
		rhs = -rhs;
	}

	Array<char> buffer(8);
	int intPart = (int)rhs;
	if(intPart != 0)
	{
		while(intPart > 0)
		{
			buffer.insert(intPart % 10);
			intPart = intPart / 10;
		}
	}
	else
	{
		buffer.insert(0);
	}

	Array<char> buffer2(8);
	float floatPart = rhs - (int)rhs;
	while(floatPart > 0.00001f && floatPart < 1.0f)
	{
		floatPart *= 10.0f;
		// console << floatPart << newline;
		buffer2.insert((char)floatPart);
		floatPart = floatPart - (int)floatPart;
		// console << floatPart << newline;
	}

	this->size = buffer.size() + buffer2.size() + neg;
	if(buffer2.size() != 0)
	{
		this->size++;
	}
	this->array = new char[this->size + 1];
	
	for(int j = 0; j < buffer.size(); j++)
	{
		this->array[j + neg] = buffer[buffer.size() - j - 1] + DIFF;
	}
	if(buffer2.size() != 0)
	{
		this->array[buffer.size() + neg] = '.';
	}
	for(int j = buffer.size() + neg; j < buffer.size() + buffer2.size(); j++)
	{
		this->array[j + 1] = buffer2[j - buffer.size()] + DIFF;
	}

	if(neg == 1)
	{
		this->array[0] = '-';
	}

	this->array[this->size] = 0x0;
}
String::String(double rhs)
{
	const int DIFF = '0' - 0;

	int neg = 0;
	if(rhs < 0)
	{
		neg = 1;
		rhs = -rhs;
	}

	Array<char> buffer(8);
	int intPart = (int)rhs;
	while(intPart > 0)
	{
		buffer.insert(intPart % 10);
		intPart = intPart / 10;
	}

	Array<char> buffer2(8);
	double floatPart = rhs - (int)rhs;
	while(floatPart > 0.00001f && floatPart < 1.0f)
	{
		floatPart *= 10.0f;
		// console << floatPart << newline;
		buffer2.insert((char)floatPart);
		floatPart = floatPart - (int)floatPart;
		// console << floatPart << newline;
	}

	this->size = buffer.size() + buffer2.size() + neg;
	if(buffer2.size() != 0)
	{
		this->size++;
	}
	this->array = new char[this->size + 1];

	for(int j = 0; j < buffer.size(); j++)
	{
		this->array[j + neg] = buffer[buffer.size() - j - 1] + DIFF;
	}
	if(buffer2.size() != 0)
	{
		this->array[buffer.size() + neg] = '.';
	}
	for(int j = buffer.size() + neg; j < buffer.size() + buffer2.size(); j++)
	{
		this->array[j + 1] = buffer2[j - buffer.size()] + DIFF;
	}

	if(neg == 1)
	{
		this->array[0] = '-';
	}

	this->array[this->size] = 0x0;
}

String::~String()
{
	// delete[] this->array;
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
String String::operator+(const String& rhs) const
{
	String str;
	str.size = this->size + rhs.size;
	str.array = new char[str.size + 1];
	memcpy(str.array, this->array, this->size);
	memcpy(str.array + this->size, rhs.array, rhs.size + 1);
	return str;
}
String String::operator+(const char* rhs) const
{
	long i = 0;
	while(rhs[i] != 0x0)
	{
		i++;
	}

	String str;
	str.size = this->size + i;
	str.array = new char[str.size + 1];
	memcpy(str.array, this->array, this->size);
	memcpy(str.array + this->size, rhs, i + 1);

	return str;
}
String String::operator+(const char& rhs) const
{
	String str;
	str.size = this->size + 1;
	str.array = new char[str.size + 1];
	memcpy(str.array, this->array, this->size);
	str.array[this->size] = rhs;
	str.array[this->size + 1] = 0x0;

	return str;
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
	// TODO: need to delete old array

	// Create new string
	this->size = rhs.size;
	this->array = new char[size + 1];
	memcpy(this->array, rhs.array, size + 1);

	return *this;
}
String& String::operator=(const char* rhs)
{
	delete[] this->array;

	long i = 0;
	while(rhs[i] != 0x0)
	{
		i++;
	}

	this->size = i;
	this->array = new char[this->size + 1];
	memcpy(this->array, rhs, this->size + 1);

	return *this;
}


bool String::operator==(const String& rhs) const
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
bool String::operator==(const char* rhs) const
{
	if(this->size == 0 && rhs[0] != 0x0)
		return false;

	for(long i = 0; i < this->size; i++)
	{
		if(this->array[i] != rhs[i])
			return false;
	}

	return true;
}
bool String::operator!=(const String& rhs) const
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
bool String::operator!=(const char* rhs) const
{
	if(this->size == 0 && rhs[0] != 0x0)
		return true;

	for(long i = 0; i < this->size; i++)
	{
		if(this->array[i] != rhs[i])
			return true;
	}

	return false;
}


bool String::operator<(const String& rhs) const
{
	for(long i = 0; i < this->size && i < rhs.size; i++)
	{
		if(this->array[i] < rhs[i])
		{
			return true;
		}
		else if(this->array[i] > rhs[i])
		{
			return false;
		}
	}
	
	if(this->size < rhs.size)
		return true;
	else
		return false;
}
bool String::operator<(const char* rhs) const
{
	long i;
	for(i = 0; i < this->size && rhs[i] != 0x0; i++)
	{
		if(this->array[i] < rhs[i])
		{
			return true;
		}
		else if(this->array[i] > rhs[i])
		{
			return false;
		}
	}

	if(this->size > i)
	{
		return false;
	}
	else
	{
		if(rhs[i] == 0x0)
			return false;
		else
			return true;
	}
}
bool String::operator<=(const String& rhs) const
{
	for(long i = 0; i < this->size && i < rhs.size; i++)
	{
		if(this->array[i] < rhs[i])
		{
			return true;
		}
		else if(this->array[i] > rhs[i])
		{
			return false;
		}
	}
	
	if(this->size <= rhs.size)
		return true;
	else
		return false;
}
bool String::operator<=(const char* rhs) const
{
	long i;
	for(i = 0; i < this->size && rhs[i] != 0x0; i++)
	{
		if(this->array[i] < rhs[i])
		{
			return true;
		}
		else if(this->array[i] > rhs[i])
		{
			return false;
		}
	}
	
	if(this->size > i)
		return false;
	else
		return true;
}
bool String::operator>(const String& rhs) const
{
	for(long i = 0; i < this->size && i < rhs.size; i++)
	{
		if(this->array[i] < rhs[i])
		{
			return false;
		}
		else if(this->array[i] > rhs[i])
		{
			return true;
		}
	}
	
	if(this->size > rhs.size)
		return true;
	else
		return false;
}
bool String::operator>(const char* rhs) const
{
	long i;
	for(i = 0; i < this->size && rhs[i] != 0x0; i++)
	{
		if(this->array[i] < rhs[i])
		{
			return false;
		}
		else if(this->array[i] > rhs[i])
		{
			return true;
		}
	}
	
	if(this->size > i)
		return true;
	else
		return false;
}
bool String::operator>=(const String& rhs) const
{
	for(long i = 0; i < this->size && i < rhs.size; i++)
	{
		if(this->array[i] < rhs[i])
		{
			return false;
		}
		else if(this->array[i] > rhs[i])
		{
			return true;
		}
	}
	
	if(this->size >= rhs.size)
		return true;
	else
		return false;
}
bool String::operator>=(const char* rhs) const
{
	long i;
	for(i = 0; i < this->size && rhs[i] != 0x0; i++)
	{
		if(this->array[i] < rhs[i])
		{
			return false;
		}
		else if(this->array[i] > rhs[i])
		{
			return true;
		}
	}
	
	if(this->size > i)
	{
		return true;
	}
	else
	{
		if(rhs[i] == 0x0)
			return true;
		else
			return false;
	}
}


String& String::operator>>(String& rhs)
{
	if(this->size == 0)
	{
		rhs = String();
		return *this;
	}

	// Cycle through extra whitesace
	int j = 0;
	for(j = 0; j < this->size; j++)
	{
		if(this->array[j] != ' ' && this->array[j] != '\n'  && this->array[j] != '\r'  && this->array[j] != '\t')
		{
			break;
		}
	}

	// Get the first space
	int i = 0;
	for(i = j; i < this->size; i++)
	{
		if(this->array[i] == ' ' || this->array[i] == '\n' || this->array[i] == '\r' || this->array[i] == '\t')
		{
			break;
		}
	}

	// If whitespace is whole word return nothing
	if(j + 1 > this->size)
	{
		rhs = String();
	}
	// Else set the rhs to that word
	else
	{
		rhs = this->subStr(j, i - j);
	}

	// Cycle through extra whitesace
	for(i = i; i < this->size; i++)
	{
		if(this->array[i] != ' ' && this->array[i] != '\n' && this->array[i] != '\r' && this->array[i] != '\t')
		{
			i--;
			break;
		}
	}

	// Take off the word + whitespace from this string
	if(i < this->size)
	{
		*this = this->subStr(i + 1);
	}
	else
	{
		*this = String();
	}

	return *this;
}

String& String::operator>>(int& rhs)
{
	String value;
	*this >> value;
	rhs = value.toInt();
	return *this;
}
String& String::operator>>(long& rhs)
{
	String value;
	*this >> value;
	rhs = value.toLong();
	return *this;
}
String& String::operator>>(float& rhs)
{
	String value;
	*this >> value;
	rhs = value.toFloat();
	return *this;
}
String& String::operator>>(double& rhs)
{
	String value;
	*this >> value;
	rhs = value.toDouble();
	return *this;
}

long String::length() const
{
	return this->size;
}

const char* String::cStr() const
{
	char* cString = new char[this->size + 1];
	memcpy(cString, this->array, this->size + 1);
	return cString;
}

String String::subStr(long startPos) const
{
	if(startPos >= this->size || startPos < 0)
	{
		throw OutOfRange();
	}

	String string;
	char* array = new char[this->size - startPos + 1];
	memcpy(array, this->array + startPos, this->size - startPos + 1);
	delete[] string.array;
	string.array = array;
	string.size = this->size - startPos;
	return string;
}
String String::subStr(long startPos, long length) const
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
	if(length - startPos > this->size || length == String::npos)
	{
		return this->subStr(startPos);
	}
	else
	{
		String string;
		char* array = new char[length + 1];
		memcpy(array, this->array + startPos, length);
		array[length] = 0x0;
		delete[] string.array;
		string.array = array;
		string.size = length;
		return string;
	}
}

Array<String> String::split(const String& delim) const
{
	long pos1 = 0;
	long pos2 = 0;
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
				list.insert(this->subStr(pos1, pos2 - pos1 - delim.size));

				if(j == 0)
				{
					i--;
				}
			}
		}
	}

	if(pos2 == 0)
	{
		list.insert(*this);
	}
	else
	{
		list.insert(this->subStr(pos2));
	}
	
	return list;
}
Array<String> String::split(const char* delim) const
{
	long pos1 = 0;
	long pos2 = 0;
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
				list.insert(this->subStr(pos1, pos2 - pos1 - j - 1));

				if(j == 0)
				{
					i--;
				}
			}
		}
	}

	if(pos2 == 0)
	{
		list.insert(*this);
	}
	else
	{
		list.insert(this->subStr(pos2));
	}

	return list;
}
Array<String> String::split(const char& delim) const
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
			list.insert(this->subStr(pos1, pos2 - pos1));
			count++;
		}
	}

	if(pos2 == -1)
	{
		list.insert(*this);
	}
	else
	{
		if(pos2 >= this->size - 1)
		{
			list.insert(String());
		}
		else
		{
			list.insert(this->subStr(pos2 + 1));
		}
	}

	return list;
}

long String::strPos(const String& search) const
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

	return String::npos;
}
long String::strPos(const char* search) const
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

	return String::npos;
}
long String::strPos(const char& search) const
{
	// Go through every character in string and compare to delim
	for(long i = 0; i < this->size; i++)
	{
		if(this->array[i] == search)
		{
			return i;
		}
	}

	return String::npos;
}
long String::strLastPos(const String& search) const
{
	// Go through every character in string and compare to delim
	long lastPos = String::npos;
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
long String::strLastPos(const char* search) const
{
	// Go through every character in string and compare to delim
	long lastPos = String::npos;
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
long String::strLastPos(const char& search) const
{
	// Go through every character in string and compare to delim
	long lastPos = String::npos;
	for(long i = 0; i < this->size; i++)
	{
		if(this->array[i] == search)
		{
			lastPos = i;
		}
	}

	return lastPos;
}
Array<long> String::strAllPos(const String& search) const
{
	Array<long> list;
	for(long i = 0; i < this->size; i++)
	{
		for(long j = 0; this->array[i + j] == search[j]; j++)
		{
			if((j + 1) >= search.size)
			{
				list.insert(i);
				break;
			}
		}
	}
	return list;
}
Array<long> String::strAllPos(const char* search) const
{
	// Go through every character in string and compare to delim
	Array<long> list;
	for(long i = 0; i < this->size; i++)
	{
		for(long j = 0; this->array[i + j] == search[j]; j++)
		{
			if(search[j + 1] == 0x0)
			{
				list.insert(i);
				break;
			}
		}
	}

	return list;
}
Array<long> String::strAllPos(const char& search) const
{
	// Go through every character in string and compare to delim
	Array<long> list;
	for(long i = 0; i < this->size; i++)
	{
		if(this->array[i] == search)
		{
			list.insert(i);
		}
	}

	return list;
}

Array<String> String::getWords() const
{
	Array<String> parts;
	String orig = *this;
	String str;
	while(orig.size != 0)
	{
		orig >> str;
		parts.insert(str);
	}

	return parts;
}

String String::insert(long pos, const String& insert) const
{
	if((pos + 1) >= this->size)
	{
		String str = this->subStr(0, pos + 1) + insert;
		return str;
	}
	else
	{
		String str = this->subStr(0, pos + 1) + insert + this->subStr(pos + 1);
		return str;
	}
}
String String::insert(long pos, const char* insert) const
{
	if((pos + 1) >= this->size)
	{
		String str = this->subStr(0, pos + 1) + insert;
		return str;
	}
	else
	{
		String str = this->subStr(0, pos + 1) + insert + this->subStr(pos + 1);
		return str;
	}
}
String String::insert(long pos, const char& insert) const
{
	if((pos + 1) >= this->size)
	{
		String str = this->subStr(0, pos + 1) + insert;
		return str;
	}
	else
	{
		String str = this->subStr(0, pos + 1) + insert + this->subStr(pos + 1);
		return str;
	}
}

String String::remove(const String& find) const
{
	String str;
	long pos = 0;
	for(long i = 0; i < this->size; i++)
	{
		for(long j = 0; this->array[i] == find[j]; j++)
		{
			i++;
			if((j + 1) >= find.size)
			{
				str += this->subStr(pos, (i - j) - pos - 1);
				pos = i;
				i--;
				break;
			}
		}
	}

	if(pos < this->size)
	{
		str += this->subStr(pos);
	}
	return str;
}
String String::remove(const char* find) const
{
	String str;
	long pos = 0;
	for(long i = 0; i < this->size; i++)
	{
		for(long j = 0; this->array[i] == find[j]; j++)
		{
			i++;
			if(find[j + 1] == 0x0)
			{
				str += this->subStr(pos, (i - j) - pos - 1);
				pos = i;
				i--;
				break;
			}
		}
	}

	if(pos < this->size)
	{
		str += this->subStr(pos);
	}
	return str;
}
String String::remove(const char& find) const
{
	String str;
	long pos = 0;
	for(long i = 0; i < this->size; i++)
	{
		if(this->array[i] == find)
		{
			str += this->subStr(pos, i - pos);
			pos = i + 1;
		}
	}

	if(pos < this->size)
	{
		str += this->subStr(pos);
	}
	return str;
}
String String::remove(long startPos, long length) const
{
	if(startPos >= this->size)
	{
		throw OutOfRange();
	}

	String str;
	delete[] str.array;
	str.array = new char[startPos + 1];
	memcpy(str.array, this->array, startPos);
	str.array[startPos] = 0x0;
	str.size = startPos;

	// Only add end of the string if length not more than rest of string
	if(this->size - startPos > length && length != String::npos)
	{
		String str2;
		delete[] str2.array;
		str2.size = this->size - (startPos + length);
		str2.array = new char[str2.size + 1];
		memcpy(str2.array, this->array + startPos + length, str2.size + 1);
		str += str2;
	}

	return str;
}
String String::replace(const String& find, const String& replace) const
{
	String str(*this);

	for(long i = 0; i < str.size; i++)
	{
		for(long j = 0; str.array[i] == find[j]; j++)
		{
			i++;
			if((j + 1) >= find.size)
			{
				// Only memcpy if search length == replace length
				if(find.size == replace.size)
				{
					memcpy(str.array + i - j - 1, replace.array, replace.size);
					i--;
					break;
				}
				// If size of two replace is different from size of find
				else
				{
					if(i < str.size)
					{
						str = str.subStr(0, i - j - 1) + replace + str.subStr(i, str.size - i);
					}
					else
					{
						str = str.subStr(0, i - j - 1) + replace;
					}
					i = i - 1 - (find.size - replace.size);
					break;
				}
			}
		}
	}

	return str;
}
String String::replace(const char* find, const char* replace) const
{
	String str(*this);

	// Get length of replace string
	long replaceLength = 0;
	for(long i = 0; replace[i] != 0x0; i++)
	{
		replaceLength = i;
	}

	for(long i = 0; i < str.size; i++)
	{
		for(long j = 0; str.array[i] == find[j]; j++)
		{
			i++;
			if(find[j + 1] == 0x0)
			{
				// Only memcpy if search length == replace length
				if(j == replaceLength)
				{
					memcpy(str.array + i - j - 1, replace, j + 1);
					i--;
					break;
				}
				else
				{
					if(i < str.size)
					{
						str = str.subStr(0, i - j - 1) + replace + str.subStr(i, str.size - i);
					}
					else
					{
						str = str.subStr(0, i - j - 1) + replace;
					}
					i = i - 1 - (j - replaceLength);
					break;
				}
			}
		}
	}

	return str;
}
String String::replace(const char& find, const char& replace) const
{
	String str(*this);
	for(long i = 0; i < this->size; i++)
	{
		if(this->array[i] == find)
		{
			str[i] = replace;
		}
	}

	return str;
}
String String::replace(int pos, int length, const String& str) const
{
	if(this->size == pos + length)
		return this->subStr(0, pos) + str;
	else
		return this->subStr(0, pos) + str + this->subStr(pos + length);
}
String String::replace(int pos, int length, const char* str) const
{
	if(this->size == pos + length)
		return this->subStr(0, pos) + str;
	else
		return this->subStr(0, pos) + str + this->subStr(pos + length);
}

String String::toLower() const
{
	const int DIFF = 'a' - 'A';

	String str(*this);
	for(long i = 0; i < this->size; i++)
	{
		if(str.array[i] >= 'A' && str.array[i] <= 'Z')
		{
			str.array[i] += DIFF;
		}
	}
	return str;
}
String String::toUpper() const
{
	const int DIFF = 'a' - 'A';

	String str(*this);
	for(long i = 0; i < this->size; i++)
	{
		if(str.array[i] >= 'a' && str.array[i] <= 'z')
		{
			str.array[i] -= DIFF;
		}
	}
	return str;
}

int String::toInt() const
{
	const int DIFF = '0' - 0;

	bool neg = false;
	long i = 0;
	if(this->array[i] == '-')
	{
		i++;
		neg = true;
	}
	else if(this->array[i] == '+')
	{
		i++;
	}

	int num = 0;
	for(i = i; i < this->size; i++)
	{
		// Ingore everything after .
		if(this->array[i] == '.')
		{
			break;
		}
		// Check that its a number
		else if(this->array[i] < '0' || this->array[i] > '9')
		{
			throw(InvalidOperation());
		}
		
		num += (this->array[i] - DIFF);
		num *= 10;
	}
	num = num / 10;

	if(neg)
	{
		return -num;
	}
	else
	{
		return num;
	}
}
long String::toLong() const
{
	const int DIFF = '0' - 0;

	bool neg = false;
	long i = 0;
	if(this->array[i] == '-')
	{
		i++;
		neg = true;
	}
	else if(this->array[i] == '+')
	{
		i++;
	}

	long num = 0;
	for(i = i; i < this->size; i++)
	{
		// Ingore everything after .
		if(this->array[i] == '.')
		{
			break;
		}
		// Check that its a number
		else if(this->array[i] < '0' || this->array[i] > '9')
		{
			throw(InvalidOperation());
		}

		num += (this->array[i] - DIFF);
		num *= 10;
	}
	num = num / 10;

	if(neg)
	{
		return -num;
	}
	else
	{
		return num;
	}
}
float String::toFloat() const
{
	const int DIFF = '0' - 0;

	bool neg = false;
	long i = 0;
	if(this->array[i] == '-')
	{
		i++;
		neg = true;
	}
	else if(this->array[i] == '+')
	{
		i++;
	}

	float num = 0.0f;
	for(i = i; i < this->size; i++)
	{
		// Compute decimal part seperately
		if(this->array[i] == '.')
		{
			float power = 1;
			for(long j = 1; i + j < this->size; j++)
			{
				if(this->array[i + j] == 'f')
				{
					break;
				}
				else if(this->array[i + j] == 'e')
				{
					i += j;
					String expString = this->subStr(i + 1);
					int exp = expString.toInt();
					for(int j = 0; exp < j; j--)
					{
						num = num / 10;
					}
					for(int j = 0; j < exp; j++)
					{
						num = num * 10;
					}
					break;
				}
				else if(this->array[i + j] < '0' || this->array[i + j] > '9')
				{
					throw(InvalidOperation());
				}

				num = num + ((float)this->array[i + j] - DIFF)  / power;
				power *= 10;
			}

			break;
		}
		else if(this->array[i] == 'e')
		{
			String expString = this->subStr(i + 1);
			int exp = expString.toInt();
			for(int j = 0; exp < j; j--)
			{
				num = num / 10;
			}
			for(int j = 0; j < exp; j++)
			{
				num = num * 10;
			}
			break;
		}
		// Check that its a number
		else if(this->array[i] < '0' || this->array[i] > '9')
		{
			throw(InvalidOperation());
		}

		num += (this->array[i] - DIFF);
		num *= 10;
	}
	num = num / 10;

	if(neg)
	{
		return -num;
	}
	else
	{
		return num;
	}
}
double String::toDouble() const
{
	const int DIFF = '0' - 0;

	bool neg = false;
	long i = 0;
	if(this->array[i] == '-')
	{
		i++;
		neg = true;
	}
	else if(this->array[i] == '+')
	{
		i++;
	}

	double num = 0.0;
	for(i = i; i < this->size; i++)
	{
		// Compute decimal part seperately
		if(this->array[i] == '.')
		{
			double power = 1;
			for(long j = 1; i + j < this->size; j++)
			{
				// Check that its a number
				if(this->array[i + j] < '0' || this->array[i + j] > '9')
				{
					throw(InvalidOperation());
				}

				num = num + ((double)this->array[i + j] - DIFF)  / power;
				power *= 10;
			}

			break;
		}
		// Check that its a number
		else if(this->array[i] < '0' || this->array[i] > '9')
		{
			throw(InvalidOperation());
		}

		num += (this->array[i] - DIFF);
		num *= 10;
	}
	num = num / 10;

	if(neg)
	{
		return -num;
	}
	else
	{
		return num;
	}
}
