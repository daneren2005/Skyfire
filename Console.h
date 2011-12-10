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

#ifndef _CONSOLE_H
#define	_CONSOLE_H

#ifdef WIN32
	#ifdef __MINGW32__
		#define newline '\n'
	#else
		#define newline "\r\n"
	#endif
#endif
#ifdef __linux__
	#define newline '\n'
#endif

#include "CString.h"

class Console
{
public:
	Console();
	Console(const Console& orig);
	virtual ~Console();

	Console& operator<<(const String& str);
	Console& operator<<(const std::string& str);
	Console& operator<<(const char* str);
	Console& operator<<(const char& str);
	Console& operator<<(const uchar& str);
	Console& operator<<(const int& num);
	Console& operator<<(const uint& num);
	Console& operator<<(const long& num);
	Console& operator<<(const ulong& num);
	Console& operator<<(const float& num);
	Console& operator<<(const double& num);
private:

};

extern Console console;

#endif	/* _CONSOLE_H */

