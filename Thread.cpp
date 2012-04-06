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

#include "Thread.h"

Thread::Thread()
{
	thread = 0x0;
}
Thread::Thread(Function<void> function)
{
	this->thread = new pthread_t*;
	*this->thread = new pthread_t;
	this->call = FunctionCall(function);
	pthread_create(*this->thread, NULL, Thread::wrapper, (void*) this);
}
Thread::Thread(const Thread& orig)
{
	this->thread = orig.thread;
	this->timer = orig.timer;
}
Thread::~Thread()
{
	
}

bool Thread::running()
{
	return thread != 0x0;
}
double Thread::runtime()
{
	return timer.totalTime();
}

void Thread::join()
{
	void* status;
	pthread_join(**thread, &status);
}

Thread& Thread::operator =(const Thread& rhs)
{
	this->thread = rhs.thread;
	this->timer = rhs.timer;
	return *this;
}
bool Thread::operator ==(const Thread& rhs)
{
	return this->thread == rhs.thread;
}
bool Thread::operator !=(const Thread& rhs)
{
	return this->thread != rhs.thread;
}

void* Thread::wrapper(void* arg)
{
	Thread* thread = (Thread*)arg;
	thread->timer.start();
	thread->call.execute();
	thread->timer.stop();
	delete *thread->thread;
	*thread->thread = 0x0;

	return nullptr;
}
