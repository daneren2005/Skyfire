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
		this->pointer = pointer;
		this->count = new long;
		(*this->count) = 1;
	}
	SharedPointer(const SharedPointer& orig)
	{
		// console << "SharedPointer constructor" << newline;
		this->pointer = orig.pointer;
		this->count = orig.count;
		(*this->count)++;
	}
	template <class U>
	SharedPointer(const SharedPointer<U> orig)
	{
		this->pointer = (T*)orig.pointer;
		this->count = orig.count;
		(*this->count)++;
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
		this->pointer = pointer;
		this->count = new long;
		(*this->count) = 1;
	}
	template <class U>
	SharedPointer& operator=(const SharedPointer<U>& rhs)
	{
		// console << "SharedPointer equal operator" << newline;
		release();
		this->pointer = (T*)rhs.pointer;
		this->count = rhs.count;
		(*this->count)++;
		return *this;
	}
	SharedPointer& operator=(const SharedPointer& rhs)
	{
		// console << "SharedPointer equal operator" << newline;
		release();
		this->pointer = rhs.pointer;
		this->count = rhs.count;
		(*this->count)++;
		return *this;
	}

	inline T& operator*()
	{
		return *this->pointer;
	}
	inline T* operator->()
	{
		return this->pointer;
	}
	inline T* getPointer()
	{
		return this->pointer;
	}
	inline long getCount()
	{
		return *this->count;
	}

	inline bool operator==(long rhs)
	{
		return this->pointer == rhs;
	}
	inline bool operator==(const SharedPointer& rhs)
	{
		return this->pointer == rhs.pointer;
	}
	inline bool operator !=(long rhs)
	{
		return this->pointer != rhs;
	}
	inline bool operator!=(const SharedPointer& rhs)
	{
		return this->pointer != rhs.pointer;
	}
private:
	T* pointer;
	long* count;

	void release()
	{
		// console << "Decreasing " << (long)pointer << newline;
		(*count)--;
		if(*count == 0)
		{
			// console << "Deleting " << (long)pointer << newline;
			delete count;
			if(pointer != 0x0)
				delete pointer;
		}
	}

	template<class U> friend class SharedPointer;
};

#endif	/* _SHAREDPOINTER_H */

