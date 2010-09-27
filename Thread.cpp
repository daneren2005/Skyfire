#include "Thread.h"
#include "Window.h"

Thread::Thread()
{
	win = NULL;
	arg = NULL;

	running = false;
}

Thread::Thread(Window* win)
{
	this->win = win;
	arg = NULL;

	running = false;
}

void Thread::start(void*(*function)(void *), void* arg)
{
	this->win = NULL;
	this->arg = arg;

	running = true;
	pthread_create(&this->id, NULL, function, (void*) this);
}

void Thread::start(void*(*function)(void *), void* arg, Window* win)
{
	this->win = win;
	this->arg = arg;
	this->function = function;

	this->running = true;
	pthread_create(&this->id, NULL, threadFunction, (void*) this);
}

void Thread::waitFor()
{
	void* status;
	pthread_join(this->id, &status);
}

void Thread::createContext()
{
	/// Enable opengl rendering
	// Get Device Context for window
	this->device = GetDC(win->winHandle);
	if(this->device == NULL)
	{
		MessageBox(NULL, TEXT("ERROR: Could not create device context."), TEXT("Error!"), MB_OK | MB_ICONERROR);
		exit(0);
	}

	// Set Pixel Format
	PIXELFORMATDESCRIPTOR pixelFormat;
	pixelFormat.nSize = sizeof(pixelFormat);
	pixelFormat.nVersion = 1;
	pixelFormat.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pixelFormat.iPixelType = PFD_TYPE_RGBA;
	pixelFormat.cColorBits = 24;
	pixelFormat.cDepthBits = 16;
	pixelFormat.iLayerType = PFD_MAIN_PLANE;
	int actualFormat = ChoosePixelFormat(this->device, &pixelFormat);
	SetPixelFormat(this->device, actualFormat, &pixelFormat);

	this->render = wglCreateContext(this->device);
	if(this->render == NULL)
	{
		MessageBox(NULL, TEXT("ERROR: Could not create rendering context."), TEXT("Error!"), MB_OK | MB_ICONERROR);
	}
	// Activate as current drawing window
	if(!wglMakeCurrent(this->device, this->render))
	{
		MessageBox(NULL, TEXT("ERROR: Could not activate rendering context."), TEXT("Error!"), MB_OK | MB_ICONERROR);
	}

	this->win->initOpenGL();
}
void Thread::getContext()
{
	if(!wglMakeCurrent(this->device, this->render))
	{
		MessageBox(NULL, TEXT("ERROR: Could not activate rendering context."), TEXT("Error!"), MB_OK | MB_ICONERROR);
	}
}

void* Thread::threadFunction(void* arg)
{
	Thread* thread = (Thread*)arg;

	if(thread->win != NULL)
	{
		thread->createContext();
	}

	while(thread->running)
	{
		if(thread->win != NULL)
		{
			pthread_mutex_lock(&thread->win->glLock);
			thread->getContext();
		}
		thread->function(thread);
		if(thread->win != NULL)
		{
			pthread_mutex_unlock(&thread->win->glLock);
		}
	}

	// Doesn't compile without returning something
	#ifdef WIN32
		return NULL;
	#endif
}