/* 
 * File:   Console.h
 * Author: scott
 *
 * Created on January 20, 2011, 11:11 AM
 */

#ifndef _CONSOLE_H
#define	_CONSOLE_H

#define newline '\n'

#include "CString.h"

class Console {
public:
	Console();
	Console(const Console& orig);
	virtual ~Console();

	Console& operator<<(const String& str);
	Console& operator<<(const std::string& str);
	Console& operator<<(const char* str);
	Console& operator<<(const char& str);
	Console& operator<<(const int& num);
	Console& operator<<(const float& num);
	Console& operator<<(const double& num);
private:

};

extern Console console;

#endif	/* _CONSOLE_H */

