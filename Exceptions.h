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

#ifndef _EXCEPTIONS_H
#define	_EXCEPTIONS_H

#include "CString.h"

class Exception
{
public:
	Exception()
	{
		this->msg = "General Exception thrown";
	}
	Exception(String msg)
	{
		this->msg = msg;
	}
	String getMsg()
	{
		return this->msg;
	}
protected:
	String msg;
};

class OutOfRange : public Exception
{
public:
	OutOfRange()
	{
		this->msg = "Exception: Out of Range";
	}	
};

class InvalidOperation : public Exception
{
public:
	InvalidOperation()
	{
		this->msg = "Exception: Attempting to make an invalid operation";
	}
};

#endif