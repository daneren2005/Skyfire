/* 
 * File:   Console.cpp
 * Author: scott
 * 
 * Created on January 20, 2011, 11:11 AM
 */

#include "Console.h"
#include <iostream>

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
	#ifdef __linux__
		std::cout << str.cStr();
	#endif
	return *this;
}
Console& Console::operator<<(const std::string& str)
{
	#ifdef __linux__
		std::cout << str;
	#endif
	return *this;
}
Console& Console::operator<<(const char* str)
{
	#ifdef __linux__
		std::cout << str;
	#endif
	return *this;
}
Console& Console::operator<<(const char& str)
{
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
	#ifdef __linux__
		std::cout << num;
	#endif
	return *this;
}
Console& Console::operator<<(const float& num)
{
	#ifdef __linux__
		std::cout << num;
	#endif
	return *this;
}
Console& Console::operator<<(const double& num)
{
	#ifdef __linux__
		std::cout << num;
	#endif
	return *this;
}

