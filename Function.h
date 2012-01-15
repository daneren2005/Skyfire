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

#ifndef _FUNCTION_H_
#define	_FUNCTION_H_

#include "GenericType.h"
#include "Console.h"
#include "Exceptions.h"
#include "SharedPointer.h"

class InvalidFunctionCall;

template <class Return, class Param>
class Function
{
public:
	Function();
	Function(const Function& orig);
	template <class Object>
	Function(const Object& o);
	Function(Return(*function)(Param));
	virtual ~Function();

	template <class Object>
	void setFunction(const Object& o);
	void setFunction(Return(*function)(Param));
	Return execute(Param param);

	Return operator()(Param param);

	template <class Object>
	Function& operator=(const Object& o);
	Function& operator=(Return(*function)(Param));
	Function& operator=(const Function& rhs);
protected:
	class ValueBase;
	template <class Object>
	class Functor;
	class FunctionPointer;

	SharedPointer<ValueBase> value;
};

template <class Return, class Param>
Function<Return, Param>::Function()
{
	value = 0x0;
}
template <class Return, class Param>
Function<Return, Param>::Function(const Function& orig)
{
	value = orig.value;
}
template <class Return, class Param>
template <class Object>
Function<Return, Param>::Function(const Object& o)
{
	(*this) = o;
}
template <class Return, class Param>
Function<Return, Param>::Function(Return(*function)(Param))
{
	(*this) = function;
}
template <class Return, class Param>
Function<Return, Param>::~Function()
{

}

template <class Return, class Param>
template <class Object>
inline void Function<Return, Param>::setFunction(const Object& o)
{
	(*this) = o;
}
template <class Return, class Param>
inline void Function<Return, Param>::setFunction(Return(*function)(Param))
{
	(*this) = function;
}
template <class Return, class Param>
Return Function<Return, Param>::execute(Param param)
{
	return (*this)(param);
}

template <class Return, class Param>
inline Return Function<Return, Param>::operator()(Param param)
{
	if(value == 0x0)
		throw InvalidFunctionCall();

	return (*value)(param);
}

template <class Return, class Param>
template <class Object>
Function<Return, Param>& Function<Return, Param>::operator=(const Object& o)
{
	value = new Functor<Object>(o);
	return *this;
}

template <class Return, class Param>
Function<Return, Param>& Function<Return, Param>::operator=(Return(*function)(Param))
{
	value = new FunctionPointer(function);
	return *this;
}

template <class Return, class Param>
Function<Return, Param>& Function<Return, Param>::operator=(const Function& rhs)
{
	value = rhs.value;
	return *this;
}

template <class Return, class Param>
class Function<Return, Param>::ValueBase
{
public:
	virtual ~ValueBase() {}
	virtual Return operator()(Param param)= 0;
};

template <class Return, class Param>
template <class Object>
class Function<Return, Param>::Functor : public Function::ValueBase
{
public:
	Functor(Object o) : o(o) {}
	virtual Return operator()(Param param) {return o(param);}
private:
	Functor() {}
	Object o;
};

template <class Return, class Param>
class Function<Return, Param>::FunctionPointer : public Function::ValueBase
{
public:
	FunctionPointer(Return(*function)(Param)) : function(function) {}
	virtual Return operator()(Param param) {return function(param);}
private:
	FunctionPointer() {}
	Return(*function)(Param);
};

class InvalidFunctionCall : public Exception
{
public:
	InvalidFunctionCall()
	{
		this->msg = "Exception: Attempting to call invalid function";
	}
};

#endif
