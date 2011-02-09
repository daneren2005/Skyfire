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