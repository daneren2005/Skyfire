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
	bool isReadLocked();
	bool isWriteLocked();

	SharedLock& operator=(const SharedLock& rhs);
	bool operator==(const SharedLock& rhs);
	bool operator!=(const SharedLock& rhs);
private:
	struct BUFFER
	{
		BUFFER()
		{
			pthread_rwlock_init(&lock, 0x0);
			read = false;
			write = false;
		}
		~BUFFER()
		{
			pthread_rwlock_destroy(&lock);
		}

		pthread_rwlock_t lock;
		bool read, write;
	};

	SharedPointer<BUFFER> buffer;
};

#endif