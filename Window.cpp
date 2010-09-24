/* 
 * File:   Window.cpp
 * Author: scott
 * 
 * Created on July 13, 2010, 10:30 PM
 */

#include <iostream>
#include "Window.h"
#include "BaseObject.h"

Window::Window()
{
	#ifdef __linux__
		surface = NULL;
	#endif

	renderScene = NULL;
	this->terminate = false;
	this->screenWidth = 640;
	this->screenHeight = 480;
	this->resolutionWidth = this->screenWidth;
	this->resolutionHeight = this->screenHeight;
	this->resolutionDistance = 100.0f;
}

Window::Window(int width, int height)
{
	#ifdef __linux__
		surface = NULL;
	#endif

	renderScene = NULL;
	this->terminate = false;
	this->screenWidth = width;
	this->screenHeight = height;
	this->resolutionWidth = this->screenWidth;
	this->resolutionHeight = this->screenHeight;
	this->resolutionDistance = 100.0f;
}

Window::~Window()
{
	this->quit();
}

void* Window::renderLoop(void* arg)
{
	Window* win = (Window*)arg;
	win->initWin();
	win->initOpenGL();

	#ifdef WIN32
		MSG msg;
	#endif
	#ifdef __linux__
		SDL_Event event;
	#endif

	while(win->terminate == false)
	{
		// Look for events
		#ifdef WIN32
			if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		#endif
		#ifdef __linux__
			if(SDL_PollEvent(&event))
			{
				win->processEvent(&event);
			}
		#endif
		// Otherwise render screen
		else
		{
			// Start to draw
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			if(win->renderScene != NULL)
				win->renderScene->render();
			
			// Update screen
			glFlush();

			#ifdef WIN32
				SwapBuffers(win->device);
			#endif
			#ifdef __linux__
				SDL_GL_SwapBuffers();
			#endif
		}

		// Keep track of how many frames are being drawn person second
		win->frameRate.draw();

		#ifdef WIN32
			// Set window title to current frame rate
			int frames = win->frameRate.framesPerSecond();
			char* temp = new char[256];
			itoa(frames, temp, 10);
			std::string temp2(temp);
			SetWindowText(win->winHandle, temp2.c_str());
		#endif
	}

	// Doesn't compile without returning something
	#ifdef WIN32
		return NULL;
	#endif
}

#ifdef __linux__
void Window::processEvent(SDL_Event* event)
{
	switch(event->type)
	{
		// TODO: Add Keyboard class for virtual mapping of key->functions
		case SDL_KEYDOWN:
			this->keyDown(&event->key.keysym);
			break;
		case SDL_KEYUP:
			this->keyUp(&event->key.keysym);
			break;
		case SDL_VIDEORESIZE:
			this->setSize(event->resize.w, event->resize.h);
			break;
		case SDL_QUIT:
			this->quit();
			break;
	}
}
#endif
#ifdef WIN32
LRESULT CALLBACK Window::WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
		case WM_CREATE:
			return 0;
		case WM_CLOSE:
			PostQuitMessage(0);
			delete _defaultCallback;
			return 0;
		case WM_SIZE:
			_defaultCallback->setSize(LOWORD(lParam), HIWORD(lParam));
			return 0;
		case WM_KEYDOWN:
			_defaultCallback->keyDown((int)wParam);
			return 0;
		case WM_KEYUP:
			_defaultCallback->keyUp((int)wParam);
			return 0;
		default:
			return DefWindowProc( hwnd, Message, wParam, lParam );
	}
}
#endif

#ifdef __linux__
void Window::keyDown(SDL_keysym* keysym)
{

	switch(keysym->sym)
	{
		case SDLK_ESCAPE:
			// exit(0);
			break;
		case SDLK_LEFT:
			input->left = true;
			break;
		case SDLK_RIGHT:
			input->right = true;
			break;
		case SDLK_UP:
			input->up = true;
			break;
		case SDLK_DOWN:
			input->down = true;
			break;
		case SDLK_PAGEUP:
			input->in = true;
			break;
		case SDLK_PAGEDOWN:
			input->out = true;
			break;
	}
}
void Window::keyUp(SDL_keysym* keysym)
{
	switch(keysym->sym)
	{
		case SDLK_ESCAPE:
			exit(0);
			break;
		case SDLK_LEFT:
			input->left = false;
			break;
		case SDLK_RIGHT:
			input->right = false;
			break;
		case SDLK_UP:
			input->up = false;
			break;
		case SDLK_DOWN:
			input->down = false;
			break;
		case SDLK_PAGEUP:
			input->in = false;
			break;
		case SDLK_PAGEDOWN:
			input->out = false;
			break;
	}
}
#endif

#ifdef WIN32
void Window::keyDown(int key)
{
	switch(key)
	{
	case VK_ESCAPE:
		input->keyDown(KEY_ESCAPE);
		break;
	case VK_UP:
		input->keyDown(KEY_UP);
		break;
	case VK_LEFT:
		input->keyDown(KEY_LEFT);
		break;
	case VK_RIGHT:
		input->keyDown(KEY_RIGHT);
		break;
	case VK_DOWN:
		input->keyDown(KEY_DOWN);
		break;
	case VK_PRIOR:
		input->keyDown(KEY_PAGEUP);
		break;
	case VK_NEXT:
		input->keyDown(KEY_PAGEDOWN);
		break;
	case 'W':
		input->keyDown(KEY_W);
		break;
	case 'A':
		input->keyDown(KEY_A);
		break;
	case 'S':
		input->keyDown(KEY_S);
		break;
	case 'D':
		input->keyDown(KEY_D);
		break;
	}
}
void Window::keyUp(int key)
{
	switch(key)
	{
	case VK_ESCAPE:
		input->keyUp(KEY_ESCAPE);
		break;
	case VK_UP:
		input->keyUp(KEY_UP);
		break;
	case VK_LEFT:
		input->keyUp(KEY_LEFT);
		break;
	case VK_RIGHT:
		input->keyUp(KEY_RIGHT);
		break;
	case VK_DOWN:
		input->keyUp(KEY_DOWN);
		break;
	case VK_PRIOR:
		input->keyUp(KEY_PAGEUP);
		break;
	case VK_NEXT:
		input->keyUp(KEY_PAGEDOWN);
		break;
	case 'W':
		input->keyUp(KEY_W);
		break;
	case 'A':
		input->keyUp(KEY_A);
		break;
	case 'S':
		input->keyUp(KEY_S);
		break;
	case 'D':
		input->keyUp(KEY_D);
		break;
	}
}
#endif

void Window::initWin()
{
	#ifdef WIN32
		// The window structure instance
		WNDCLASSEX winStruct;

		// Size of structure
		winStruct.cbSize        = sizeof(WNDCLASSEX);
		// Window Style
		winStruct.style         = CS_OWNDC;
		// Windows Callback procedure
		winStruct.lpfnWndProc   = Window::WndProc;
		// Extra memory allocation for this class
		winStruct.cbClsExtra    = 0;
		// Extra memory allocation per window
		winStruct.cbWndExtra    = 0;
		// Handle for window instance
		winStruct.hInstance     = this->programHandle;
		// Icon displayed for alt + tab
		winStruct.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
		// Mouse cursor
		winStruct.hCursor       = LoadCursor(NULL, IDC_ARROW);
		// Color of background
		winStruct.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
		// Name of menu resource
		winStruct.lpszMenuName  = NULL;
		// Name to identify structure instance by
		winStruct.lpszClassName =	TEXT("test");
		// Icon displayed top left cornor of window and taskbar
		winStruct.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

		// Register the window instance
		if(!RegisterClassEx(&winStruct))
		{
			MessageBox(0, TEXT("Error Registering Class!"), TEXT("Error!"), MB_ICONSTOP | MB_OK);
			exit(0);
		}

		// Create the actual window and pass paramaters in
		winHandle = CreateWindowEx(WS_EX_STATICEDGE, TEXT("test"), TEXT("Test Form"), 
			WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, CW_USEDEFAULT, CW_USEDEFAULT, this->screenWidth, this->screenHeight, NULL, NULL, programHandle, NULL);
		if(winHandle == NULL)
		{
			MessageBox(0, TEXT("Error Creating Window!"), TEXT("Error!"), MB_ICONSTOP | MB_OK);
			exit(0);
		}

		/// Enable opengl rendering
		// Get Device Context for window
		this->device = GetDC(winHandle);
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
		// Initialize rendering context
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

		ShowWindow(winHandle, 1);
		UpdateWindow(winHandle);
	#endif

	#ifdef __linux__
		// Setup SDL
		if(SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			std::cout << "Video Initialization failed" << std::endl;
			exit(1);
		}

		// Setup SDL flags
		const SDL_VideoInfo* videoInfo;
		videoInfo = SDL_GetVideoInfo();
		if(!videoInfo)
		{
			std::cout << "Video Query failed" << std::endl;
			exit(1);
		}
		videoFlags = SDL_OPENGL;
		videoFlags |= SDL_GL_DOUBLEBUFFER;
		videoFlags |= SDL_HWPALETTE;
		videoFlags |= SDL_RESIZABLE;
		if(videoInfo->hw_available)
			videoFlags |= SDL_HWSURFACE;
		else
			videoFlags |= SDL_SWSURFACE;
		if(videoInfo->blit_hw)
			videoFlags |= SDL_HWACCEL;
		// videoFlags |= SDL_FULLSCREEN;

		// Setup SDL surface
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		this->surface = SDL_SetVideoMode(this->screenWidth, this->screenHeight, 24, videoFlags);
		if(!this->surface)
		{
			std::cout << "Video Mode Set failed" << std::endl;
			exit(1);
		}
	#endif
}

void Window::initOpenGL()
{
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	this->resetScreen();
}

void Window::setSize(int width, int height)
{
	this->screenWidth = width;
	this->screenHeight = height;

	this->resetScreen();
}
void Window::setResolution(GLdouble width, GLdouble height, GLdouble distance)
{
	this->resolutionWidth = width;
	this->resolutionHeight = height;
	this->resolutionDistance = distance;

	this->resetScreen();
}
void Window::resetScreen()
{
	std::cout << this->screenWidth << std::endl << this->screenHeight << std::endl;

	// TODO: find out if this is actually keeping the same resolution
	glViewport(0, 0, (GLsizei)this->screenWidth, (GLsizei)this->screenHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// gluPerspective(45, (float)this->width/this->height, 0.1f, 100.0f);
	GLdouble aspectRatio = (GLdouble)this->screenWidth / (GLdouble)this->screenHeight;
	/*if(this->screenWidth <= this->screenHeight)
		glOrtho(-(this->resolutionWidth / 2), (this->resolutionWidth / 2), 
				-(this->resolutionHeight / 2 / aspectRatio), (this->resolutionHeight / 2 / aspectRatio) / aspectRatio,
				this->resolutionDistance, -this->resolutionDistance);
	else
		glOrtho(-(this->resolutionWidth / 2 / aspectRatio), (this->resolutionWidth / 2 / aspectRatio)
				, -(this->resolutionHeight / 2), (this->resolutionHeight / 2), this->resolutionDistance, -this->resolutionDistance);*/
	gluPerspective( 45.0f, aspectRatio, 0.1f, this->resolutionDistance);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Window::start(HINSTANCE program)
{
	#ifdef WIN32
		this->programHandle = program;
		_defaultCallback = this;
	#endif

	// Setup render loop
	pthread_create(&this->renderThread, NULL, renderLoop, (void*)this);
}

void Window::wait()
{
	void* status;
	pthread_join(this->renderThread, &status);
}

void Window::quit()
{
	this->terminate = true;

	#ifdef WIN32
		wglMakeCurrent(this->device, NULL);
		wglDeleteContext(this->render);
	#endif
	#ifdef __linux__
		delete this->surface;
		SDL_Quit();
	#endif
}

void Window::setScene(Scene* newScene)
{
	this->renderScene = newScene;
}
void Window::setInput(Input* input)
{
	this->input = input;
}

