#ifndef _THREAD_H
#define	_THREAD_H

#ifdef WIN32
	#include <windows.h>
	#include <GL/glut.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>

#include <pthread.h>
#include "StopWatch.h"

class Window;

class Thread
{
public:
	Thread();

	void start(void*(*function)(void *), void* arg);
	void start(void*(*function)(void *), void* arg, void*(*startFunction)(void *));
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
	void*(*function)(void *);
	void*(*startFunction)(void *);
	pthread_t id;

	static void* threadFunction(void* arg);

	StopWatch clock;
	double period;
	int counter;
	int returnCounter;
};

#endif
