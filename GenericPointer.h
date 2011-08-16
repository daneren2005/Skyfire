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

#ifndef _GENERIC_POINTER_H
#define	_GENERIC_POINTER_H

class GenericPointer
{
public:
	GenericPointer();
	GenericPointer(const GenericPointer& orig);
	template <class T>
	GenericPointer(T orig);

	GenericPointer& operator =(GenericPointer& rhs);
	template <class T>
	GenericPointer& operator =(T rhs);

	bool operator==(const GenericPointer& rhs);
	template <class T>
	bool operator==(T rhs);
	bool operator!=(const GenericPointer& rhs);
	template <class T>
	bool operator!=(T rhs);

	template <class T>
	operator T();
	void* operator*();
	template <class T>
	T* cast();

private:
	void* value;
};

template <class T>
GenericPointer::GenericPointer(T orig)
{
	this->value = (void*)orig;
}

template <class T>
GenericPointer& GenericPointer::operator=(T rhs)
{
	this->value = (void*)rhs;
	return *this;
}

template <class T>
bool GenericPointer::operator==(T rhs)
{
	return ((T)value) == rhs;
}
template <class T>
bool GenericPointer::operator!=(T rhs)
{
	return ((T)value) != rhs;
}

template <class T>
GenericPointer::operator T()
{
	return (T)value;
}

template <class T>
T* GenericPointer::cast()
{
	return (T*)value;
}

#endif
