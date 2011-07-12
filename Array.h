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

#ifndef _ARRAY_H
#define	_ARRAY_H

#include <iostream>

template <class T>
class Array
{
public:
	Array();
	Array(unsigned long size);
	Array(const Array& orig);
	~Array();

	virtual T& operator[](unsigned col);
	virtual const T& operator[](unsigned col) const; 

	unsigned long size();
	unsigned long size() const;
	unsigned long reserved();
	unsigned long reserved() const;

	void insert(const T& value);
	void resize(unsigned long newSize);

	T* getPointer();
	const T* getPointer() const;
protected:
	T* array;
	unsigned long used;
	unsigned long allocated;
};

template <class T>
Array<T>::Array()
{
	this->used = 0;
	this->allocated = 1;
	this->array = new T[this->allocated];
}

template <class T>
Array<T>::Array(unsigned long size)
{
	this->used = 0;
	this->allocated = size;
	this->array = new T[size];
}

template <class T>
Array<T>::Array(const Array<T> &orig)
{
	this->used = orig.used;
	this->allocated = orig.used;
	this->array = new T[this->allocated];
	for(unsigned long i = 0; i < this->used; i++)
	{
		this->array[i] = orig.array[i];
	}
}

template <class T>
Array<T>::~Array()
{
	// delete[] array;
}

template <class T>
T& Array<T>::operator[](unsigned col)
{
	if(col > this->used)
		this->used = col + 1;

	return this->array[col];
}

template <class T>
const T& Array<T>::operator[](unsigned col) const
{
	return this->array[col];
}

template <class T>
unsigned long Array<T>::size()
{
	return this->used;
}
template <class T>
unsigned long Array<T>::size() const
{
	return this->used;
}

template <class T>
unsigned long Array<T>::reserved()
{
	return this->used;
}
template <class T>
unsigned long Array<T>::reserved() const
{
	return this->used;
}

template <class T>
void Array<T>::insert(const T& value)
{
	if(this->used >= this->allocated)
	{
		this->resize(this->allocated * 2);
	}

	this->array[this->used] = value;
	this->used++;
}

template <class T>
void Array<T>::resize(unsigned long newSize)
{
	T* toDelete = this->array;
	this->array = new T[newSize];
	for(unsigned long i = 0; i < this->used && i < newSize; i++)
	{
		this->array[i] = toDelete[i];
	}
	
	this->allocated = newSize;
	if(newSize < this->used)
	{
		this->used = newSize;
	}

	// TODO: find a way to safely delete old array
	// delete[] toDelete;
}

template <class T>
T* Array<T>::getPointer()
{
	return this->array;
}
template <class T>
const T* Array<T>::getPointer() const
{
	return this->array;
}

#endif
