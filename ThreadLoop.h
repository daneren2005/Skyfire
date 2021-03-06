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

#ifndef _THREAD_LOOP_H
#define	_THREAD_LOOP_H

#include "GenericType.h"
#include <pthread.h>
#include "Timer.h"
#include "Types.h"
#include "Function.h"

class ThreadLoop
{
public:
	ThreadLoop();

	void start(Function<void, ThreadLoop*> function, GenericType arg);
	void start(Function<void, ThreadLoop*> function, GenericType arg, Function<void, ThreadLoop*> startFunction);
	void startMain(Function<void, ThreadLoop*> function, GenericType arg);
	void startMain(Function<void, ThreadLoop*> function, GenericType arg, Function<void, ThreadLoop*> startFunction);
	void stop();
	void pause();
	void resume();
	void currentWaitFor();
	
	void sleep(double seconds);

	GenericType getArg();

	void setTicksPerSecond(int ticks = 0);
	void setTimeBetweenTicks(double seconds = 0);
	// Get set tick period
	double getTimeBetweenTicks();
	// Get how many times per second thread is running
	int getTicksPerSecond();
	double getTimeSinceTick();
	double getRunningTime();
	
	static void currentSleep(double seconds);
private:
	GenericType arg;

	bool quit;
	bool running;
	Function<void, ThreadLoop*> function;
	Function<void, ThreadLoop*> startFunction;
	pthread_t id;

	static void* threadFunction(void* arg);

	Timer clock;
	double period;
	double timeSinceTick;
	int counter;
	int returnCounter;
	ulong sleepTime;
};

#endif
