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

#ifndef _LOCK_H
#define	_LOCK_H

#include "SharedPointer.h"
#include <pthread.h>

class Condition;

class Lock
{
public:
	Lock();
	Lock(const Lock& orig);
	virtual ~Lock();

	void lock();
	bool tryLock();
	void unlock();
	bool isLocked();

	Lock& operator=(const Lock& rhs);
	bool operator==(const Lock& rhs);
	bool operator!=(const Lock& rhs);

	friend class Condition;
private:
	struct BUFFER
	{
		BUFFER()
		{
			pthread_mutex_init(&lock, 0x0);
			locked = false;
		}
		~BUFFER()
		{
			pthread_mutex_destroy(&lock);
		}

		pthread_mutex_t lock;
		bool locked;
	};

	SharedPointer<BUFFER> buffer;
};

#endif
