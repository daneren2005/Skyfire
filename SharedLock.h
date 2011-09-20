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

#ifndef _SHARED_LOCK_H
#define	_SHARED_LOCK_H

#include "Condition.h"
#include <pthread.h>

class SharedLock
{
public:
	SharedLock();
	SharedLock(const SharedLock& orig);
	virtual ~SharedLock();

	void readLock();
	void writeLock();
	bool tryReadLock();
	bool tryWriteLock();
	void unlock();
	bool isLocked();
	bool isWriteLocked();
	long readLocks();

	SharedLock& operator=(const SharedLock& rhs);
	bool operator==(const SharedLock& rhs);
	bool operator!=(const SharedLock& rhs);
private:
	struct BUFFER
	{
		Lock lock;
		Condition read, write;
		long readers;
		bool writing;
		long readWaiting, writeWaiting;
	};

	SharedPointer<BUFFER> buffer;
};

#endif
