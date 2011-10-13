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
#include "Types.h"
#include "Comparison.h"

template <class T>
class Array
{
public:
	Array();
	Array(ulong size);
	Array(const Array& orig);
	virtual ~Array();

	virtual T& operator[](unsigned col);
	virtual const T& operator[](unsigned col) const; 

	ulong size();
	ulong size() const;
	ulong reserved();
	ulong reserved() const;

	void insert(const T& value);
	void sort();
	template <class Compare>
	void sort(Compare c);
	void resize(ulong newSize);

	T* getPointer();
	const T* getPointer() const;
protected:
	T* array;
	ulong used;
	ulong allocated;
};

template <class T>
Array<T>::Array()
{
	this->used = 0;
	this->allocated = 1;
	this->array = new T[this->allocated];
}

template <class T>
Array<T>::Array(ulong size)
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
	for(ulong i = 0; i < this->used; i++)
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
ulong Array<T>::size()
{
	return this->used;
}
template <class T>
ulong Array<T>::size() const
{
	return this->used;
}

template <class T>
ulong Array<T>::reserved()
{
	return this->used;
}
template <class T>
ulong Array<T>::reserved() const
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
void Array<T>::sort()
{
	this->sort(LessThan<T>());
}

template <class T>
template <class Compare>
void Array<T>::sort(Compare c)
{
	// Heapify the array
	for(long start = this->used / 2 - 1; start >= 0; start--)
	{
		// Bubble down
		ulong i = start;
		while(i * 2 + 2 <= this->used)
		{
			ulong swap = i;
			ulong k = i * 2 + 1;
			if(c(array[swap], array[k]))
				swap = k;
			if(k + 2 <= this->used && c(array[swap], array[k + 1]))
				swap = k + 1;

			if(swap != i)
			{
				T temp = array[i];
				array[i] = array[swap];
				array[swap] = temp;
				i = swap;
			}
			else
			{
				i = this->used + 1;
			}
		}
	}

	// Pop top and move to back of array to sort
	for(ulong end = this->used - 1; end > 0; end--)
	{
		// Swap top and end of heap
		T temp = array[end];
		array[end] = array[0];
		array[0] = temp;

		// Bubble down
		ulong i = 0;
		while(i * 2 + 2 <= end)
		{
			ulong swap = i;
			ulong k = i * 2 + 1;
			if(c(array[i], array[k]))
				swap = k;
			if(k + 2 <= end && c(array[swap], array[k + 1]))
				swap = k + 1;

			if(swap != i)
			{
				temp = array[i];
				array[i] = array[swap];
				array[swap] = temp;
				i = swap;
			}
			else
			{
				i = this->used;
			}
		}
	}
}

template <class T>
void Array<T>::resize(ulong newSize)
{
	T* toDelete = this->array;
	this->array = new T[newSize];
	for(ulong i = 0; i < this->used && i < newSize; i++)
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
