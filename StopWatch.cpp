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

#include "StopWatch.h"

StopWatch::StopWatch()
{
	this->running = false;
	this->totalSeconds = 0;
	this->previousTotal = 0;
	this->previousElapsed = 0;

	#ifdef WIN32
		QueryPerformanceFrequency(&this->ticksPerSecond);
	#endif
}

StopWatch::StopWatch(const StopWatch& orig)
{
	this->totalSeconds = orig.totalSeconds;
	this->previousTotal = orig.previousTotal;
	this->previousElapsed = orig.previousElapsed;
	this->running = orig.running;

	#ifdef WIN32
		this->ticksPerSecond = orig.ticksPerSecond;
		QueryPerformanceCounter(&this->now);
	#endif
}

void StopWatch::start()
{
	if(this->running == false)
	{
		this->running = true;

		#ifdef WIN32
			QueryPerformanceCounter(&this->now);
			this->previousElapsed = (float)this->now.QuadPart / (float)this->ticksPerSecond.QuadPart;
			this->previousTotal = (float)this->now.QuadPart / (float)this->ticksPerSecond.QuadPart;
		#endif

		#ifdef __linux__
			clock_gettime(CLOCK_REALTIME, &this->now);
			this->previousElapsed = this->now.tv_sec + this->now.tv_nsec / 1000000000.0;
			this->previousTotal = this->now.tv_sec + this->now.tv_nsec / 1000000000.0;
		#endif
	}
}

void StopWatch::stop()
{
	if(this->running == true)
	{
		this->running = false;

		#ifdef WIN32
			QueryPerformanceCounter(&this->now);
			this->totalSeconds += ((float)this->now.QuadPart / (float)this->ticksPerSecond.QuadPart) - this->previousTotal;
		#endif

		#ifdef __linux__
			clock_gettime(CLOCK_REALTIME, &this->now);
			this->totalSeconds += (this->now.tv_sec + this->now.tv_nsec / 1000000000.0) - this->previousTotal;
		#endif
	}
}

void StopWatch::reset()
{
	this->totalSeconds = 0;
	
	if(this->running == true)
	{
		#ifdef WIN32
			QueryPerformanceCounter(&this->now);
			this->previousElapsed = (float)this->now.QuadPart / (float)this->ticksPerSecond.QuadPart;
			this->previousTotal = (float)this->now.QuadPart / (float)this->ticksPerSecond.QuadPart;
		#endif

		#ifdef __linux__
			clock_gettime(CLOCK_REALTIME, &this->now);
			this->previousElapsed = this->now.tv_sec + this->now.tv_nsec / 1000000000.0;
			this->previousTotal = this->now.tv_sec + this->now.tv_nsec / 1000000000.0;
		#endif
	}
}

double StopWatch::totalTime()
{
	if(this->running == true)
	{
		#ifdef WIN32
			QueryPerformanceCounter(&this->now);
			this->totalSeconds += ((float)this->now.QuadPart / (float)this->ticksPerSecond.QuadPart) - this->previousTotal;
			this->previousTotal = (float)this->now.QuadPart / (float)this->ticksPerSecond.QuadPart;
		#endif

		#ifdef __linux__
			clock_gettime(CLOCK_REALTIME, &this->now);
			this->totalSeconds += (this->now.tv_sec + this->now.tv_nsec / 1000000000.0) - this->previousTotal;
			this->previousTotal = this->now.tv_sec + this->now.tv_nsec / 1000000000.0;
		#endif
	}

	return this->totalSeconds;
}

double StopWatch::elapsedTime()
{
	if(this->running == true)
	{
		double diff = 0.0;

		#ifdef WIN32
			QueryPerformanceCounter(&this->now);
			diff = ((float)this->now.QuadPart / (float)this->ticksPerSecond.QuadPart) - this->previousElapsed;
			this->previousElapsed = (float)this->now.QuadPart / (float)this->ticksPerSecond.QuadPart;
		#endif

		#ifdef __linux__
			clock_gettime(CLOCK_REALTIME, &this->now);
			diff = (this->now.tv_sec + this->now.tv_nsec / 1000000000.0) - this->previousElapsed;
			this->previousElapsed = this->now.tv_sec + this->now.tv_nsec / 1000000000.0;
		#endif

		return diff;
	}
	else
	{
		return 0.0;
	}
}