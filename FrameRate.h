#ifndef _FRAMERATE_H
#define	_FRAMERATE_H

#include "StopWatch.h"

class FrameRate
{
public:
	FrameRate();

	void draw();
	int framesPerSecond();
private:
	StopWatch clock;
	int counter;
	int returnCounter;
};

#endif
