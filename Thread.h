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

#ifndef _THREAD_H
#define	_THREAD_H

#include <GL/gl.h>
#include <GL/glu.h>

#include <pthread.h>
#include "StopWatch.h"

class Window;

class Thread
{
public:
	Thread();

	void start(void*(*function)(Thread*), void* arg);
	void start(void*(*function)(Thread*), void* arg, void*(*startFunction)(Thread*));
	void startMain(void*(*function)(Thread*), void* arg);
	void startMain(void*(*function)(Thread*), void* arg, void*(*startFunction)(Thread*));
	void stop();
	void pause();
	void resume();
	void waitFor();

	void* getArg();

	void setTicksPerSecond(int ticks = 0);
	int getTicksPerSecond();
private:
	void* arg;

	bool quit;
	bool running;
	void*(*function)(Thread*);
	void*(*startFunction)(Thread*);
	pthread_t id;

	static void* threadFunction(void* arg);

	StopWatch clock;
	double period;
	int counter;
	int returnCounter;
};

#endif
