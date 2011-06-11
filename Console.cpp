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

#include "Console.h"
#include <iostream>

#ifdef WIN32
	#include <windows.h>
#endif

Console console = Console();

Console::Console()
{
}

Console::Console(const Console& orig)
{
}

Console::~Console()
{
}

Console& Console::operator<<(const String& str)
{
	#ifdef WIN32
		OutputDebugString(str.cStr());
	#endif
	#ifdef __linux__
		std::cout << str.cStr();
	#endif
	return *this;
}
Console& Console::operator<<(const std::string& str)
{
	#ifdef WIN32
		OutputDebugString(str.c_str());
	#endif
	#ifdef __linux__
		std::cout << str;
	#endif
	return *this;
}
Console& Console::operator<<(const char* str)
{
	#ifdef WIN32
		OutputDebugString(str);
	#endif
	#ifdef __linux__
		std::cout << str;
	#endif
	return *this;
}
Console& Console::operator<<(const char& str)
{
	#ifdef WIN32
		OutputDebugString(String(str).cStr());
	#endif
	#ifdef __linux__
		if(str == '\n')
			std::cout << std::endl;
		else
			std::cout << str;
	#endif
	return *this;
}

Console& Console::operator<<(const int& num)
{
	#ifdef WIN32
		OutputDebugString(String(num).cStr());
	#endif
	#ifdef __linux__
		std::cout << num;
	#endif
	return *this;
}
Console& Console::operator<<(const long& num)
{
	#ifdef WIN32
		OutputDebugString(String(num).cStr());
	#endif
	#ifdef __linux__
		std::cout << num;
	#endif
	return *this;
}
Console& Console::operator<<(const float& num)
{
	#ifdef WIN32
		OutputDebugString(String(num).cStr());
	#endif
	#ifdef __linux__
		std::cout << num;
	#endif
	return *this;
}
Console& Console::operator<<(const double& num)
{
	#ifdef WIN32
		OutputDebugString(String(num).cStr());
	#endif
	#ifdef __linux__
		std::cout << num;
	#endif
	return *this;
}

