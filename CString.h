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
	String(const char* rhs, long size);
	String(char rhs);
	String(int rhs);
	String(long rhs);
	String(float rhs);
	String(double rhs);
	~String();

	// Operator Overloading
	char& operator[](unsigned pos);
	const char& operator[](unsigned pos) const;
	String operator+(const String& rhs) const;
	String operator+(const char* rhs) const;
	String operator+(const char& rhs) const;
	String& operator+=(const String& rhs);
	String& operator+=(const char* rhs);
	String& operator+=(const char& rhs);
	String& operator=(const String& rhs);
	String& operator=(const char* rhs);
	bool operator==(const String& rhs) const;
	bool operator==(const char* rhs) const;
	bool operator!=(const String& rhs) const;
	bool operator!=(const char* rhs) const;
	bool operator<(const String& rhs) const;
	bool operator<(const char* rhs) const;
	bool operator<=(const String& rhs) const;
	bool operator<=(const char* rhs) const;
	bool operator>(const String& rhs) const;
	bool operator>(const char* rhs) const;
	bool operator>=(const String& rhs) const;
	bool operator>=(const char* rhs) const;
	String& operator>>(String& rhs);
	String& operator>>(int& rhs);
	String& operator>>(long& rhs);
	String& operator>>(float& rhs);
	String& operator>>(double& rhs);


	// String Accessors
	long length() const;
	const char* cStr() const;
	String subStr(long startPos) const;
	String subStr(long startPos, long length) const;
	Array<String> split(const String& delim) const;
	Array<String> split(const char* delim) const;
	Array<String> split(const char& delim) const;
	long strPos(const String& search) const;
	long strPos(const char* search) const;
	long strPos(const char& search) const;
	long strLastPos(const String& search) const;
	long strLastPos(const char* search) const;
	long strLastPos(const char& search) const;
	Array<long> strAllPos(const String& search) const;
	Array<long> strAllPos(const char* search) const;
	Array<long> strAllPos(const char& search) const;
	Array<String> getWords() const;

	// String manipulation
	String insert(long pos, const String& insert) const;
	String insert(long pos, const char* insert) const;
	String insert(long pos, const char& insert) const;
	String remove(const String& find) const;
	String remove(const char* find) const;
	String remove(const char& find) const;
	String remove(long startPos, long length) const;
	String replace(const String& find, const String& replace) const;
	String replace(const char* find, const char* replace) const;
	String replace(const char& find, const char& replace) const;
	String replace(int pos, int length, const String& replace) const;
	String replace(int pos, int length, const char* replace) const;

	// String conversions
	String toLower() const;
	String toUpper() const;
	int toInt() const;
	long toLong() const;
	float toFloat() const;
	double toDouble() const;
private:
	char* array;
	long size;
};

#endif
