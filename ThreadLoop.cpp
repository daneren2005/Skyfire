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

#include "ThreadLoop.h"
#include "Console.h"

ThreadLoop::ThreadLoop()
{
	this->quit = false;
	this->running = false;

	this->period = 0;
	this->timeSinceTick = 0.0f;
	this->counter = 0;
	this->returnCounter = 0;
	this->sleepTime = 0;
}

void ThreadLoop::start(Function<void, ThreadLoop*> function, GenericType arg)
{
	this->arg = arg;
	this->running = true;
	this->quit = false;
	this->function = function;
	clock.start();

	pthread_create(&this->id, NULL, threadFunction, (void*) this);
}
void ThreadLoop::start(Function<void, ThreadLoop*> function, GenericType arg, Function<void, ThreadLoop*> startFunction)
{
	this->arg = arg;
	this->quit = false;
	this->running = true;
	this->function = function;
	this->startFunction = startFunction;
	clock.start();

	pthread_create(&this->id, NULL, threadFunction, (void*) this);
}

void ThreadLoop::startMain(Function<void, ThreadLoop*> function, GenericType arg)
{
	this->arg = arg;
	this->running = true;
	this->quit = false;
	this->function = function;
	clock.start();

	ThreadLoop::threadFunction((void*)this);
}
void ThreadLoop::startMain(Function<void, ThreadLoop*> function, GenericType arg, Function<void, ThreadLoop*> startFunction)
{
	this->arg = arg;
	this->quit = false;
	this->running = true;
	this->function = function;
	this->startFunction = startFunction;
	clock.start();

	ThreadLoop::threadFunction((void*)this);
}

void ThreadLoop::stop()
{
	clock.stop();
	this->quit = true;
}
void ThreadLoop::pause()
{
	clock.stop();
	this->running = false;
}
void ThreadLoop::resume()
{
	clock.start();
	this->running = true;
}

void ThreadLoop::currentWaitFor()
{
	void* status;
	pthread_join(this->id, &status);
}

void ThreadLoop::sleep(double seconds)
{
	sleepTime = (ulong)(seconds * 1000);
}

GenericType ThreadLoop::getArg()
{
	return this->arg;
}

void ThreadLoop::setTicksPerSecond(int ticks)
{
	this->period = (ticks != 0) ? 1.0 / ticks : 0;
}
void ThreadLoop::setTimeBetweenTicks(double seconds)
{
	this->period = seconds;
}
double ThreadLoop::getTimeBetweenTicks()
{
	return this->period;
}
int ThreadLoop::getTicksPerSecond()
{
	return returnCounter;
}
double ThreadLoop::getTimeSinceTick()
{
	return timeSinceTick;
}
double ThreadLoop::getRunningTime()
{
	return clock.totalTime();
}

void ThreadLoop::currentSleep(double seconds)
{
	ulong sleepTime = (ulong)(seconds * 1000);
	#ifdef WIN32
		Sleep(sleepTime);
	#endif
	#ifdef __linux__
		usleep(sleepTime * 1000);
	#endif
}

void* ThreadLoop::threadFunction(void* arg)
{
	ThreadLoop* thread = (ThreadLoop*)arg;
	if(thread->startFunction.isSet())
		thread->startFunction(thread);
	
	thread->clock.elapsedTime();
	while(!thread->quit)
	{
		if(thread->running)
		{
			if(thread->sleepTime > 0)
			{
				#ifdef WIN32
					Sleep(thread->sleepTime);
				#endif
				#ifdef __linux__
					usleep(thread->sleepTime * 1000);
				#endif

				thread->sleepTime = 0;
			}
			
			double startTime = thread->clock.totalTime();
			thread->timeSinceTick = thread->clock.elapsedTime();
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
					ulong sleepTime = (ulong)((thread->period - diff) * 1000);
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
