#ifndef _THREAD_H
#define	_THREAD_H

#ifdef WIN32
	#include <windows.h>
#endif

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <pthread.h>

class Window;

class Thread
{
	friend class Window;
public:
	Thread();
	Thread(Window* win);

	void start(void*(*function)(void *), void* arg);
	void start(void*(*function)(void *), void* arg, Window* win);
	void waitFor();

	void createContext();
	void getContext();
private:
	Window* win;
	void* arg;

	bool running;
	void*(*function)(void *);
	pthread_t id;

	#ifdef WIN32
		HDC device;
		HGLRC render;
	#endif

	static void* threadFunction(void* arg);
};

#endif
