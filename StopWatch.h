/* 
 * File:   StopWatch.h
 * Author: scott
 *
 * Created on July 6, 2010, 8:12 PM
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

