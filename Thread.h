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

#ifndef _THREAD_H__
#define	_THREAD_H__

#include "FunctionCall.h"
#include "Tuple.h"
#include "Function.h"
#include "Timer.h"
#include <pthread.h>

class Thread
{
public:
	Thread();
	Thread(Function<void> function);
	template <class Param>
	Thread(Function<void, Param> function, Param arg);
	Thread(const Thread& orig);
	virtual ~Thread();

	bool running();
	double runtime();
	void join();

	Thread& operator =(const Thread& rhs);
	bool operator ==(const Thread& rhs);
	bool operator !=(const Thread& rhs);
private:
	static void* wrapper(void* arg);

	SharedPointer<pthread_t*> thread;
	Timer timer;

	FunctionCall call;
};

template <class Param>
Thread::Thread(Function<void, Param> function, Param arg)
{
	this->thread = new pthread_t*;
	*this->thread = new pthread_t;
	this->call = FunctionCall(function, arg);
	pthread_create(*this->thread, NULL, Thread::wrapper, (void*) this);
}

#endif