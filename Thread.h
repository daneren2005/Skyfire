#ifndef _THREAD_H
#define	_THREAD_H

#ifdef WIN32
	#include <windows.h>
	#include <GL/glut.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>

#include <pthread.h>

class Window;

class Thread
{
public:
	Thread();

	void start(void*(*function)(void *), void* arg);
	void start(void*(*function)(void *), void* arg, void*(*startFunction)(void *));
	void stop();
	void waitFor();

	void* getArg();
private:
	void* arg;

	bool running;
	void*(*function)(void *);
	void*(*startFunction)(void *);
	pthread_t id;

	static void* threadFunction(void* arg);
};

#endif
