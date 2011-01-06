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
	~String();

	// Operator Overloading
	char& operator[](unsigned pos);
	const char& operator[](unsigned pos) const;
	String operator+(const String& rhs);
	String operator+(const char* rhs);
	String operator+(const char& rhs);
	String& operator+=(const String& rhs);
	String& operator+=(const char* rhs);
	String& operator+=(const char& rhs);
	String& operator=(const String& rhs);
	String& operator=(const char* rhs);
	bool operator==(const String& rhs);
	bool operator==(const char* rhs);
	bool operator!=(const String& rhs);
	bool operator!=(const char* rhs);

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
	String toLower();
	String toUpper();
private:
	char* array;
	long size;
};

#endif
