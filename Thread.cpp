#include "Thread.h"
#include "Window.h"

Thread::Thread()
{
	arg = NULL;

	quit = false;
	running = false;
}

void Thread::start(void*(*function)(void *), void* arg)
{
	this->arg = arg;
	this->running = true;
	this->quit = false;
	this->function = function;
	this->startFunction = NULL;

	pthread_create(&this->id, NULL, threadFunction, (void*) this);
}
void Thread::start(void*(*function)(void *), void* arg, void*(*startFunction)(void *))
{
	this->arg = arg;
	this->quit = false;
	this->running = true;
	this->function = function;
	this->startFunction = startFunction;

	pthread_create(&this->id, NULL, threadFunction, (void*) this);
}

void Thread::stop()
{
	this->quit = true;
}
void Thread::pause()
{
	this->running = false;
}
void Thread::resume()
{
	this->running = true;
}

void Thread::waitFor()
{
	void* status;
	pthread_join(this->id, &status);
}

void* Thread::getArg()
{
	return this->arg;
}

void* Thread::threadFunction(void* arg)
{
	Thread* thread = (Thread*)arg;

	if(thread->startFunction != NULL)
		thread->startFunction(thread);
	
	while(!thread->quit)
	{
		if(thread->running)
			thread->function(thread);
	}

	// Doesn't compile without returning something
	return NULL;
}
