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
#include "Window.h"

#include "Console.h"

Thread::Thread()
{
	this->arg = NULL;

	this->quit = false;
	this->running = false;

	this->period = 0;
	this->counter = 0;
	this->returnCounter = 0;
}

void Thread::start(void*(*function)(void *), void* arg)
{
	this->arg = arg;
	this->running = true;
	this->quit = false;
	this->function = function;
	this->startFunction = NULL;
	clock.start();

	pthread_create(&this->id, NULL, threadFunction, (void*) this);
}
void Thread::start(void*(*function)(void *), void* arg, void*(*startFunction)(void *))
{
	this->arg = arg;
	this->quit = false;
	this->running = true;
	this->function = function;
	this->startFunction = startFunction;
	clock.start();

	pthread_create(&this->id, NULL, threadFunction, (void*) this);
}

void Thread::stop()
{
	clock.stop();
	this->quit = true;
}
void Thread::pause()
{
	clock.stop();
	this->running = false;
}
void Thread::resume()
{
	clock.start();
	this->running = true;
}

void Thread::waitFor()
{
	void* status;
	pthread_join(this->id, &status);
}

void* Thread::getArg()
{
	return this->arg;
}

void Thread::setTicksPerSecond(int ticks)
{
	this->period = 1.0 / ticks;
}
int Thread::getTicksPerSecond()
{
	return returnCounter;
}

void* Thread::threadFunction(void* arg)
{
	Thread* thread = (Thread*)arg;

	if(thread->startFunction != NULL)
		thread->startFunction(thread);
	
	while(!thread->quit)
	{
		if(thread->running)
		{
			double startTime = thread->clock.totalTime();
			thread->function(thread);
			double endTime = thread->clock.totalTime();

			// Get counter stats
			thread->counter++;
			if(endTime >= 1.0)
			{
				thread->returnCounter = thread->counter;
				thread->counter = 0;
				thread->clock.reset();
			}

			// <= 0 period means run as fast as possible
			if(thread->period > 0)
			{
				double diff = endTime - startTime;
				// Only run if it took less than the period time
				if(thread->period > diff)
				{
					int sleepTime = (thread->period - diff) * 1000;
					#ifdef WIN32
						Sleep(sleepTime);
					#endif
					#ifdef __linux__
						usleep(sleepTime * 1000);
					#endif
				}
			}
		}
	}

	// Doesn't compile without returning something
	return NULL;
}
