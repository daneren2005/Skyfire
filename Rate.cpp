#include "Rate.h"

#ifdef WIN32
	#include <windows.h>
#endif

#ifdef __linux__
	#include <unistd.h>
	#include <iostream>
#endif

Rate::Rate()
{
	clock.start();
	counter = 0;
	returnCounter = 0;

	this->period = 0.0;
	this->start = 0.0;
}
Rate::Rate(int limit)
{
	clock.start();
	counter = 0;
	returnCounter = 0;

	this->period = 1.0 / limit;
	this->start = 0.0;
}

void Rate::executeStart()
{
	if(this->period != 0)
	{
		this->start = clock.totalTime();
	}
}

void Rate::executeEnd()
{
	counter++;
	double end = clock.totalTime();
	if(end > 1.0)
	{
		returnCounter = counter;
		counter = 0;
		clock.reset();
	}

	if(this->period != 0)
	{
		if(start > end)
			end++;

		int sleepTime = (period - (end - start)) * 1000;
		if(sleepTime > 1)
			#ifdef WIN32
				Sleep(sleepTime);
			#endif
			#ifdef __linux__
				usleep(sleepTime * 1000);
			#endif
	}
}

int Rate::ticksPerSecond()
{
	return returnCounter;
}