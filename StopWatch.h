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

#ifndef _STOPWATCH_H
#define	_STOPWATCH_H

#ifdef WIN32
	#include <windows.h>
#endif

#ifdef __linux__
	#include <time.h>
#endif

class StopWatch
{
public:
	// Initilization
	StopWatch();
	StopWatch(const StopWatch& orig);

	// Run functions
	void start();
	void stop();
	void reset();
	double totalTime();
	double elapsedTime();
private:	
	bool running;

	double totalSeconds;
	double previousTotal;
	double previousElapsed;

	#ifdef WIN32
		LARGE_INTEGER ticksPerSecond;
		LARGE_INTEGER now;
	#endif
	#ifdef __linux__
		timespec now;
	#endif
};

#endif	/* _STOPWATCH_H */

