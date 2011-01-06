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

	long size();
	long max();

	void insert(T value);
	void resize(unsigned long newSize);
protected:
	T* array;
	unsigned long _size;
	unsigned long _max;
};

template <class T>
Array<T>::Array()
{
	this->_size = 1;
	this->_max = 1;
	this->array = new T[this->_size];
}

template <class T>
Array<T>::Array(unsigned long size)
{
	this->_size = size;
	this->_max = size;
	this->array = new T[size];
}

template <class T>
Array<T>::Array(const Array<T> &orig)
{
	this->_size = orig._size;
	this->_max = this->_size;
	this->array = new T[this->_size];
	for(int i = 0; i < this->_size; i++)
	{
		this->array[i] = orig.array[i];
	}
}

template <class T>
Array<T>::~Array()
{
	delete[] array;
}

template <class T>
T& Array<T>::operator[](unsigned col)
{
	if(col >= this->_size)
	{
		if(col >= this->_max)
		{
			this->resize(this->_max * 2);
		}
		
		this->_size = col + 1;
		return this->array[col];
	}
	else
	{
		return this->array[col];
	}
}

template <class T>
const T& Array<T>::operator[](unsigned col) const
{
	if(col >= this->_size)
	{
		// TODO: figure out how to throw exception in Array class
		std::cout << "This si where the error is" << std::endl;
	}
	else
	{
		return array[col];
	}
}

template <class T>
long Array<T>::size()
{
	return this->_size;
}

template <class T>
long Array<T>::max()
{
	return this->_max;
}

template <class T>
void Array<T>::insert(T value)
{
	if(this->_size >= this->_max)
	{
		this->resize(this->_max * 2);
	}

	this->_size++;
	this->array[this->_size] = value;
}

template <class T>
void Array<T>::resize(unsigned long newSize)
{
	T* toDelete = this->array;
	this->array = new T[newSize];
	for(unsigned long i = 0; i < _size && i < newSize; i++)
	{
		this->array[i] = toDelete[i];
	}
	
	this->_max = newSize;
	if(this->_size < newSize)
	{
		this->_size = newSize;
	}

	// TODO: find a way to safely delete old array
	// delete[] toDelete;
}

#endif
