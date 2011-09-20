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

#ifndef _CONDITION_H
#define	_CONDITION_H

#include "Lock.h"

class Condition
{
public:
	Condition();
	Condition(Condition& orig);
	~Condition();

	// Release a lock while waiting for signal
	void wait(Lock lock);
	// Condition satisfied for a single waiting thread
	void signal();
	// Condition satisfied for all waiting threads
	void broadcast();

	Condition& operator=(Condition& rhs);
	bool operator==(Condition& rhs);
	bool operator!=(Condition& rhs);
private:
	struct BUFFER
	{
		BUFFER()
		{
			pthread_cond_init(&condition, 0x0);
		}
		~BUFFER()
		{
			pthread_cond_destroy(&condition);
		}

		pthread_cond_t condition;
	};

	SharedPointer<BUFFER> buffer;
};

#endif
