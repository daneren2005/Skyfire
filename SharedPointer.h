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

#ifndef _SHAREDPOINTER_H
#define	_SHAREDPOINTER_H

template <class T>
class SharedPointer
{
public:
	SharedPointer(T* pointer = 0x0)
	{
		// console << "Pointer constructor" << newline;
		counter = new Counter(pointer);
	}
	SharedPointer(const SharedPointer& orig)
	{
		// console << "SharedPointer constructor" << newline;
		aquire(orig.counter);
	}
	virtual ~SharedPointer()
	{
		// console << "Destructor" << newline;
		release();
	}

	SharedPointer& operator=(T* pointer)
	{
		// console << "Pointer equal operator" << newline;
		release();
		counter = new Counter(pointer);
	}
	SharedPointer& operator=(const SharedPointer& rhs)
	{
		// console << "SharedPointer equal operator" << newline;
		release();
		aquire(rhs.counter);
		return *this;
	}

	inline T& operator*()
	{
		return *counter->pointer;
	}
	inline T* operator->()
	{
		return counter->pointer;
	}
	inline T* getPointer()
	{
		return counter->pointer;
	}
	inline int getCount()
	{
		return counter->count;
	}
private:
	class Counter
	{
	public:
		Counter(T* pointer)
		{
			// console << "Initializing " << (long)pointer << newline;
			this->pointer = pointer;
			count = 1;
		}
		~Counter()
		{
			if(pointer != 0x0)
				delete pointer;
		}

		T* pointer;
		int count;
	};

	Counter* counter;

	void aquire(Counter* counter)
	{
		// console << "Increasing " << (long)counter->pointer << newline;
		this->counter = counter;
		this->counter->count++;
	}
	void release()
	{
		// console << "Decreasing " << (long)counter->pointer << newline;
		counter->count--;
		if(counter->count == 0)
		{
			// console << "Deleting " << (long)counter->pointer << newline;
			delete counter;
		}
	}
};

#endif	/* _SHAREDPOINTER_H */

