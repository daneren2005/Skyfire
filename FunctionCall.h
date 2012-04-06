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

#ifndef _FUNCTION_CALL_H_
#define	_FUNCTION_CALL_H_

#include "SharedPointer.h"
#include "Function.h"
#include "MemberFunction.h"

class FunctionCall
{
public:
	FunctionCall();
	FunctionCall(Function<void> function);
	template <class Param>
	FunctionCall(Function<void, Param> function, Param arg);
	template <class Object, class Param>
	FunctionCall(MemberFunction<Object, void, Param> function, Param arg);
	FunctionCall(const FunctionCall& orig);
	virtual ~FunctionCall();
	
	virtual void execute();

	FunctionCall& operator =(const FunctionCall& rhs);
	bool operator ==(const FunctionCall& rhs);
	bool operator !=(const FunctionCall& rhs);
private:
	class ContainerBase;
	template <class Param>
	class Container;
	template <class Object, class Param>
	class ContainerMember;

	SharedPointer<ContainerBase> container;
};

template <class Param>
FunctionCall::FunctionCall(Function<void, Param> function, Param arg)
{
	this->container = new FunctionCall::Container<Param>(function, arg);
}
template <class Object, class Param>
FunctionCall::FunctionCall(MemberFunction<Object, void, Param> function, Param arg)
{
	this->container = new FunctionCall::ContainerMember<Object, Param>(function, arg);
}

class FunctionCall::ContainerBase
{
public:
	ContainerBase(Function<void> function)
	{
		this->function = function;
	}
	virtual ~ContainerBase() {}

	virtual void execute()
	{
		function();
	}
protected:
	ContainerBase() {}

	Function<void> function;
};

template <class Param>
class FunctionCall::Container : public ContainerBase
{
public:
	Container(Function<void, Param> function, Param arg) : ContainerBase()
	{
		this->function = function;
		this->arg = arg;
	}
	virtual ~Container() {}

	virtual void execute()
	{
		function(arg);
	}
private:
	Function<void, Param> function;
	Param arg;
};

template <class Object, class Param>
class FunctionCall::ContainerMember : public ContainerBase
{
public:
	ContainerMember(MemberFunction<Object, void, Param> function, Param arg) : ContainerBase()
	{
		this->function = function;
		this->arg = arg;
	}
	virtual ~ContainerMember() {}

	virtual void execute()
	{
		function.execute(arg);
	}
private:
	MemberFunction<Object, void, Param> function;
	Param arg;
};

#endif
