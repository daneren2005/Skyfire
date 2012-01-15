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

#ifndef _MEMBER_FUNCTION_H_
#define	_MEMBER_FUNCTION_H_

#include "Function.h"

template <class Object, class Return, class Param>
class MemberFunction : public Function<Return, Param>
{
public:
	MemberFunction();
	MemberFunction(Object* o);
	MemberFunction(Return(Object::*function)(Param));
	MemberFunction(Return(Object::*function)(Param), Object* o);
	MemberFunction(const MemberFunction& orig);
	virtual ~MemberFunction();

	void setObject(Object* obj);
	Object* getObject();
	void setFunction(Return(Object::*function)(Param));

	MemberFunction& operator=(Return(Object::*function)(Param));
	MemberFunction& operator=(const MemberFunction& rhs);
private:
	class MemberPointer;

	Function<Return, Param>::value;
	Object* o;

	// Don't allow calling of these
	void setFunction(const Object& o);
	void setFunction(Return(*function)(Param));
};

template <class Object, class Return, class Param>
MemberFunction<Object, Return, Param>::MemberFunction() : Function<Return, Param>()
{
	this->o = 0x0;
}
template <class Object, class Return, class Param>
MemberFunction<Object, Return, Param>::MemberFunction(Object* o) : Function<Return, Param>()
{
	this->o = o;
}
template <class Object, class Return, class Param>
MemberFunction<Object, Return, Param>::MemberFunction(Return(Object::*function)(Param))
{
	(*this) = function;
}
template <class Object, class Return, class Param>
MemberFunction<Object, Return, Param>::MemberFunction(Return(Object::*function)(Param), Object* o)
{
	(*this) = function;
	this->o = o;
}
template <class Object, class Return, class Param>
MemberFunction<Object, Return, Param>::MemberFunction(const MemberFunction& orig)
{
	value = orig.value;
	o = orig.o;
}
template <class Object, class Return, class Param>
MemberFunction<Object, Return, Param>::~MemberFunction()
{
	
}

template <class Object, class Return, class Param>
void MemberFunction<Object, Return, Param>::setObject(Object* obj)
{
	this->o = obj;
	if(value != 0x0)
		((MemberPointer*)value.getPointer())->o = o;
}

template <class Object, class Return, class Param>
Object* MemberFunction<Object, Return, Param>::getObject()
{
	return this->o;
}

template <class Object, class Return, class Param>
void MemberFunction<Object, Return, Param>::setFunction(Return(Object::*function)(Param))
{
	(*this) = function;
}

template <class Object, class Return, class Param>
MemberFunction<Object, Return, Param>& MemberFunction<Object, Return, Param>::operator=(Return(Object::*function)(Param))
{
	value = new MemberPointer(function);
	if(o != 0x0)
		((MemberPointer*)value.getPointer())->o = o;
	
	return *this;
}
template <class Object, class Return, class Param>
MemberFunction<Object, Return, Param>& MemberFunction<Object, Return, Param>::operator=(const MemberFunction& rhs)
{
	value = rhs.value;
	o = rhs.o;
	
	return *this;
}

template <class Object, class Return, class Param>
class MemberFunction<Object, Return, Param>::MemberPointer : public Function<Return, Param>::ValueBase
{
public:
	MemberPointer(Return(Object::*function)(Param)) : o(0x0), function(function) {}
	virtual Return operator()(Param param)
	{
		if(o == 0x0)
			throw InvalidFunctionCall();

		return ((*o).*function)(param);
	}

	Object* o;
private:
	MemberPointer() {}
	Return(Object::*function)(Param);
};

#endif
