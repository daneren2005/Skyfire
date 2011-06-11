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

#ifndef _CSTRING_H
#define	_CSTRING_H

#include "Array.h"

class String
{
public:
	// Public constants
	static const long npos = -1;

	// Constructor + Destructor
	String();
	String(const String& rhs);
	String(const char* rhs);
	String(int rhs);
	String(long rhs);
	String(float rhs);
	String(double rhs);
	~String();

	// Operator Overloading
	char& operator[](unsigned pos);
	const char& operator[](unsigned pos) const;
	String operator+(const String& rhs);
	String operator+(const String& rhs) const;
	String operator+(const char* rhs);
	String operator+(const char* rhs) const;
	String operator+(const char& rhs);
	String operator+(const char& rhs) const;
	String& operator+=(const String& rhs);
	String& operator+=(const char* rhs);
	String& operator+=(const char& rhs);
	String& operator=(const String& rhs);
	String& operator=(const char* rhs);
	bool operator==(const String& rhs);
	bool operator==(const String& rhs) const;
	bool operator==(const char* rhs);
	bool operator==(const char* rhs) const;
	bool operator!=(const String& rhs);
	bool operator!=(const String& rhs) const;
	bool operator!=(const char* rhs);
	bool operator!=(const char* rhs) const;
	bool operator<(const String& rhs);
	bool operator<(const String& rhs) const;
	bool operator<(const char* rhs);
	bool operator<(const char* rhs) const;
	bool operator<=(const String& rhs);
	bool operator<=(const String& rhs) const;
	bool operator<=(const char* rhs);
	bool operator<=(const char* rhs) const;
	bool operator>(const String& rhs);
	bool operator>(const String& rhs) const;
	bool operator>(const char* rhs);
	bool operator>(const char* rhs) const;
	bool operator>=(const String& rhs);
	bool operator>=(const String& rhs) const;
	bool operator>=(const char* rhs);
	bool operator>=(const char* rhs) const;
	String& operator>>(String& rhs);
	String& operator>>(int& rhs);
	String& operator>>(long& rhs);
	String& operator>>(float& rhs);
	String& operator>>(double& rhs);


	// String Accessors
	long length();
	const char* cStr() const;
	String subStr(long startPos);
	String subStr(long startPos, long length);
	Array<String> split(const String& delim);
	Array<String> split(const char* delim);
	Array<String> split(const char& delim);
	long strPos(const String& search);
	long strPos(const char* search);
	long strPos(const char& search);
	long strLastPos(const String& search);
	long strLastPos(const char* search);
	long strLastPos(const char& search);
	Array<long> strAllPos(const String& search);
	Array<long> strAllPos(const char* search);
	Array<long> strAllPos(const char& search);
	Array<String> getWords();

	// String manuipulation
	String insert(long pos, const String& insert);
	String insert(long pos, const char* insert);
	String insert(long pos, const char& insert);
	String remove(const String& find);
	String remove(const char* find);
	String remove(const char& find);
	String remove(long startPos, long length);
	String replace(const String& find, const String& replace);
	String replace(const char* find, const char* replace);
	String replace(const char& find, const char& replace);

	// String conversions
	String toLower();
	String toUpper();
	int toInt();
	long toLong();
	float toFloat();
	double toDouble();
private:
	char* array;
	long size;
};

#endif
