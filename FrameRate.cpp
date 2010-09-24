#include "FrameRate.h"

#include <iostream>

FrameRate::FrameRate()
{
	clock.start();
	counter = 0;
	returnCounter = 0;
}

void FrameRate::draw()
{
	counter++;
	std::cout << clock.totalTime() << std::endl;
	double temp = clock.totalTime();
	if(clock.totalTime() > 1.0)
	{
		returnCounter = counter;
		counter = 0;
		clock.reset();
	}
}

int FrameRate::framesPerSecond()
{
	return returnCounter;
}