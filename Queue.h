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

#ifndef _Queue_H__
#define	_Queue_H__

#include "Lock.h"
#include "Condition.h"
#include "Types.h"
#include "Exceptions.h"

template <class T>
class Queue
{
public:
	Queue();
	Queue(ulong size);
	Queue(Queue& orig);
	virtual ~Queue();

	// Insert a value, resize on full
	void insert(const T& value);
	// Insert value, wait on full
	void insertWait(const T& value);
	// Check top value
	T front();
	// Check top value, wait if empty
	T frontWait();
	// Remove value, throw error on empty
	T remove();
	// Remove value, wait on empty
	T removeWait();
	bool search(const T& value);

	// Get size
	ulong size();
	// Get size of buffer
	ulong reserved();
	bool empty();

	void waitTillEmpty();
	ulong waitingThreads();

	Queue& operator=(Queue& rhs);

	class Iterator;
	Iterator begin();
protected:
	T* array;
	ulong _front;
	ulong _back;
	ulong allocated;

	Lock lock;
	Condition _empty, _full;
	ulong waiting;
};

template <class T>
Queue<T>::Queue()
{
	array = new T[4];
	_front = 0;
	_back = 0;
	allocated = 4;
	waiting = 0;
}
template <class T>
Queue<T>::Queue(ulong size)
{
	array = new T[size];
	_front = 0;
	_back = 0;
	allocated = size;
	waiting = 0;
}
template <class T>
Queue<T>::Queue(Queue& orig)
{
	orig.lock.lock();

	this->_front = orig._front;
	this->_back = orig._back;
	this->allocated = orig.allocated;
	this->array = new T[allocated];
	this->waiting = 0;

	// Copy data
	if(_front < _back)
	{
		for(ulong i = _front; i < _back; i++)
		{
			this->array[i] = orig.array[i];
		}
	}
	else
	{
		for(ulong i = _front; i < allocated; i++)
		{
			this->array[i] = orig.array[i];
		}
		for(ulong i = 0; i < _back; i++)
		{
			this->array[i] = orig.array[i];
		}
	}

	orig.lock.unlock();
}
template <class T>
Queue<T>::~Queue()
{
	lock.lock();
	delete array;
	lock.unlock();
}

template <class T>
void Queue<T>::insert(const T& value)
{
	lock.lock();
	array[_back] = value;

	_back++;
	// End of array
	if(_back >= allocated)
	{
		_back = 0;
	}
	// Out of room, resize
	if(_back == _front)
	{
		T* newArray = new T[allocated * 2];
		ulong j = 0;
		
		// Copy first half
		for(ulong i = _front; i < allocated; i++, j++)
		{
			newArray[j] = array[i];
		}
		_front = 0;
		// Copy second half
		for(ulong i = 0; i < _back; i++, j++)
		{
			newArray[j] = array[i];
		}
		_back = j;

		allocated *= 2;
		array = newArray;
	}

	_empty.signal();
	lock.unlock();
}
template <class T>
void Queue<T>::insertWait(const T& value)
{
	lock.lock();
	// Out of room, wait for room
	ulong temp = _back + 1;
	while((temp == _front) || (temp >= allocated && _front == 0))
	{
		waiting++;
		_full.wait(lock);
		waiting--;
	}

	array[_back] = value;

	_back++;
	// End of array
	if(_back >= allocated)
	{
		_back = 0;
	}

	_empty.signal();
	lock.unlock();
}

template <class T>
T Queue<T>::front()
{
	lock.lock();
	if(_front == _back)
	{
		lock.unlock();
		throw OutOfRange();
	}

	T val = array[_front];
	lock.unlock();
	return val;
}
template <class T>
T Queue<T>::frontWait()
{
	lock.lock();
	while(_front == _back)
	{
		waiting++;
		_empty.wait(lock);
		waiting--;
	}

	T val = array[_front];
	lock.unlock();
	return val;
}
template <class T>
T Queue<T>::remove()
{
	lock.lock();
	if(_front == _back)
	{
		lock.unlock();
		throw OutOfRange();
	}

	T val = array[_front];

	_front++;
	if(_front >= allocated)
		_front = 0;

	_full.signal();
	lock.unlock();
	return val;
}
template <class T>
T Queue<T>::removeWait()
{
	lock.lock();
	while(_front == _back)
	{
		waiting++;
		_empty.wait(lock);
		waiting--;
	}

	T val = array[_front];

	_front++;
	if(_front >= allocated)
		_front = 0;

	_full.signal();
	lock.unlock();
	return val;
}
template <class T>
bool Queue<T>::search(const T& value)
{
	lock.lock();
	if(_back == _front)
	{
		lock.unlock();
		return false;
	}

	ulong end;
	if(_back > _front)
		end = _back;
	else
		end = allocated;

	for(ulong i = _front; i < end; i++)
	{
		if(array[i] == value)
		{
			lock.unlock();
			return true;
		}
	}

	if(_back != end)
	{
		for(ulong i = 0; i < _back; i++)
		{
			if(array[i] == value)
			{
				lock.unlock();
				return true;
			}
		}
	}
	
	lock.unlock();
	return false;
}

template <class T>
ulong Queue<T>::size()
{
	lock.lock();
	ulong size;
	if(_back < _front)
		size = (allocated - _front) + _back;
	else
		size =  _back - _front;
	lock.unlock();
	return size;
}
template <class T>
ulong Queue<T>::reserved()
{
	return allocated;
}
template <class T>
bool Queue<T>::empty()
{
	lock.lock();
	bool val = _back == _front;
	lock.unlock();
	return val;
}

template <class T>
void Queue<T>::waitTillEmpty()
{
	lock.lock();
	while(_front != _back)
	{
		waiting++;
		_full.wait(lock);
		waiting--;
	}
	lock.unlock();
}
template <class T>
ulong Queue<T>::waitingThreads()
{
	return waiting;
}

template <class T>
Queue<T>& Queue<T>::operator=(Queue& rhs)
{
	this->lock.lock();
	delete[] array;

	rhs.lock.lock();

	this->_front = rhs._front;
	this->_back = rhs._back;
	this->allocated = rhs.allocated;
	this->array = new T[allocated];
	this->waiting = 0;

	// Copy data
	if(_front < _back)
	{
		for(ulong i = _front; i < _back; i++)
		{
			this->array[i] = rhs.array[i];
		}
	}
	else
	{
		for(ulong i = _front; i < allocated; i++)
		{
			this->array[i] = rhs.array[i];
		}
		for(ulong i = 0; i < _back; i++)
		{
			this->array[i] = rhs.array[i];
		}
	}

	rhs.lock.unlock();
	this->lock.unlock();
	return *this;
}

template <class T>
class Queue<T>::Iterator
{
public:
	Iterator(Queue<T>* queue)
	{
		this->queue = queue;
		pos = queue->_front;
	}
private:
	Queue<T>* queue;
	ulong pos;
};

template <class T>
typename Queue<T>::Iterator Queue<T>::begin()
{
	return Iterator(this);
}

#endif
