#ifndef _Rate_H
#define	_Rate_H

#include "StopWatch.h"

class Rate
{
public:
	Rate();
	Rate(int limit);

	void executeStart();
	void executeEnd();
	int ticksPerSecond();
private:
	StopWatch clock;
	int counter;
	int returnCounter;

	double start;
	double period;
};

#endif
