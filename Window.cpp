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

#include <iostream>
#include "Window.h"
#include "BaseObject.h"

Window::Window()
{
	renderer = NULL;
	this->terminate = false;
	this->screenWidth = 640;
	this->screenHeight = 480;
	this->resolutionWidth = this->screenWidth;
	this->resolutionHeight = this->screenHeight;
	this->resolutionDistance = 100.0f;

	#ifdef WIN32
		programHandle = NULL;
		winHandle = NULL;
		device = NULL;
		render = NULL;
	#endif
	#ifdef __linux__
		surface = NULL;
	#endif

	pthread_mutex_init(&this->glLock, NULL);

	this->input = new Input();
}

Window::Window(int width, int height)
{
	renderer = NULL;
	this->terminate = false;
	this->screenWidth = width;
	this->screenHeight = height;
	this->resolutionWidth = this->screenWidth;
	this->resolutionHeight = this->screenHeight;
	this->resolutionDistance = 100.0f;

	#ifdef WIN32
		programHandle = NULL;
		winHandle = NULL;
		device = NULL;
		render = NULL;
	#endif
	#ifdef __linux__
		surface = NULL;
	#endif

	pthread_mutex_init(&this->glLock, NULL);

	this->input = new Input();
}

Window::~Window()
{
	pthread_mutex_destroy(&this->glLock);
	this->quit();
}

void Window::start()
{
	#ifdef WIN32
		this->programHandle = GetModuleHandle(0);
		_defaultCallback = this;
	#endif

	// Start rendering
	renderThread.setTicksPerSecond(60);
	renderThread.start(renderFunction, this, initWin);
}

void Window::wait()
{
	renderThread.currentWaitFor();
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

void Window::initWin(Thread* arg)
{
	Thread* thread = (Thread*)arg;
	Window* win = (Window*)thread->getArg();

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
		winStruct.hInstance     = win->programHandle;
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
		win->winHandle = CreateWindowEx(WS_EX_STATICEDGE, TEXT("test"), TEXT("Test Form"),
			WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, CW_USEDEFAULT, CW_USEDEFAULT, win->screenWidth, win->screenHeight, NULL, NULL, win->programHandle, NULL);
		if(win->winHandle == NULL)
		{
			MessageBox(0, TEXT("Error Creating Window!"), TEXT("Error!"), MB_ICONSTOP | MB_OK);
			exit(0);
		}

		/// Enable opengl rendering
		// Get Device Context for window
		win->device = GetDC(win->winHandle);
		if(win->device == NULL)
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
		int actualFormat = ChoosePixelFormat(win->device, &pixelFormat);
		SetPixelFormat(win->device, actualFormat, &pixelFormat);
		// Initialize rendering context
		win->render = wglCreateContext(win->device);
		if(win->render == NULL)
		{
			MessageBox(NULL, TEXT("ERROR: Could not create rendering context."), TEXT("Error!"), MB_OK | MB_ICONERROR);
		}
		// Activate as current drawing window
		if(!wglMakeCurrent(win->device, win->render))
		{
			MessageBox(NULL, TEXT("ERROR: Could not activate rendering context."), TEXT("Error!"), MB_OK | MB_ICONERROR);
		}

		ShowWindow(win->winHandle, 1);
		UpdateWindow(win->winHandle);
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
		win->videoFlags = SDL_OPENGL;
		win->videoFlags |= SDL_GL_DOUBLEBUFFER;
		win->videoFlags |= SDL_HWPALETTE;
		win->videoFlags |= SDL_RESIZABLE;
		if(videoInfo->hw_available)
			win->videoFlags |= SDL_HWSURFACE;
		else
			win->videoFlags |= SDL_SWSURFACE;
		if(videoInfo->blit_hw)
			win->videoFlags |= SDL_HWACCEL;
		// videoFlags |= SDL_FULLSCREEN;

		// Setup SDL surface
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		win->surface = SDL_SetVideoMode(win->screenWidth, win->screenHeight, 24, win->videoFlags);
		if(!win->surface)
		{
			std::cout << "Video Mode Set failed" << std::endl;
			exit(1);
		}
	#endif

	win->initOpenGL();
}

void Window::initOpenGL()
{
	glShadeModel(GL_SMOOTH);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	this->resetScreen();
}

void Window::renderFunction(Thread* arg)
{
	Thread* thread = (Thread*)arg;
	Window* win = (Window*)thread->getArg();

	// win->frameRate.executeStart();

	// Proccess events
	#ifdef WIN32
		MSG msg;
		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	#endif
	#ifdef __linux__
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			win->processEvent(&event);
		}
	#endif

	// render screen
	// Start to draw
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(win->renderer != NULL)
		win->renderer->render();

	// Update screen
	glFlush();

	#ifdef WIN32
		SwapBuffers(win->device);
	#endif
	#ifdef __linux__
		SDL_GL_SwapBuffers();
	#endif

	// Keep track of how many frames are being drawn person second
	// win->frameRate.executeEnd();

	#ifdef WIN32
		// Set window title to current frame rate
		int frames = thread->getTicksPerSecond();
		String tmp(frames);
		SetWindowText(win->winHandle, tmp.cStr());
	#endif
	#ifdef __linux__
		int frames = thread->getTicksPerSecond();
		String tmp(frames);
		SDL_WM_SetCaption(tmp.cStr(), "Orcid");
	#endif
}

#ifdef __linux__
void Window::processEvent(SDL_Event* event)
{
	switch(event->type)
	{
		case SDL_MOUSEMOTION:
			this->mouseMove(event->motion.x, event->motion.y);
			break;
		case SDL_MOUSEBUTTONDOWN:
			this->mouseDown(event->button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			this->mouseUp(event->button.button);
			break;
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

void Window::mouseMove(int x, int y)
{
	input->mouseMove(x, y);
}
void Window::mouseDown(int button)
{
	switch(button)
	{
	case SDL_BUTTON_LEFT:
		input->keyDown(BUTTON_LEFT);
		break;
	case SDL_BUTTON_RIGHT:
		input->keyDown(BUTTON_RIGHT);
		break;
	case SDL_BUTTON_MIDDLE:
		input->keyDown(BUTTON_MIDDLE);
		break;
	case SDL_BUTTON_WHEELUP:
		input->keyDown(WHEEL_UP);
		break;
	case SDL_BUTTON_WHEELDOWN:
		input->keyDown(WHEEL_DOWN);
	default:
		break;
	}
}
void Window::mouseUp(int button)
{
	switch(button)
	{
	case SDL_BUTTON_LEFT:
		input->keyUp(BUTTON_LEFT);
		break;
	case SDL_BUTTON_RIGHT:
		input->keyUp(BUTTON_RIGHT);
		break;
	case SDL_BUTTON_MIDDLE:
		input->keyUp(BUTTON_MIDDLE);
		break;
	case SDL_BUTTON_WHEELUP:
		input->keyUp(WHEEL_UP);
		break;
	case SDL_BUTTON_WHEELDOWN:
		input->keyUp(WHEEL_DOWN);
	default:
		break;
	}
}

void Window::keyDown(SDL_keysym* keysym)
{

	switch(keysym->sym)
	{
	case SDLK_ESCAPE:
		input->keyDown(KEY_ESCAPE);
		break;
	case SDLK_UP:
		input->keyDown(KEY_UP);
		break;
	case SDLK_LEFT:
		input->keyDown(KEY_LEFT);
		break;
	case SDLK_RIGHT:
		input->keyDown(KEY_RIGHT);
		break;
	case SDLK_DOWN:
		input->keyDown(KEY_DOWN);
		break;
	case SDLK_PAGEUP:
		input->keyDown(KEY_PAGEUP);
		break;
	case SDLK_PAGEDOWN:
		input->keyDown(KEY_PAGEDOWN);
		break;
	case SDLK_w:
		input->keyDown(KEY_W);
		break;
	case SDLK_a:
		input->keyDown(KEY_A);
		break;
	case SDLK_s:
		input->keyDown(KEY_S);
		break;
	case SDLK_d:
		input->keyDown(KEY_D);
		break;
	default:
		break;
	}
}
void Window::keyUp(SDL_keysym* keysym)
{
	switch(keysym->sym)
	{
	case SDLK_ESCAPE:
		input->keyUp(KEY_ESCAPE);
		break;
	case SDLK_UP:
		input->keyUp(KEY_UP);
		break;
	case SDLK_LEFT:
		input->keyUp(KEY_LEFT);
		break;
	case SDLK_RIGHT:
		input->keyUp(KEY_RIGHT);
		break;
	case SDLK_DOWN:
		input->keyUp(KEY_DOWN);
		break;
	case SDLK_PAGEUP:
		input->keyUp(KEY_PAGEUP);
		break;
	case SDLK_PAGEDOWN:
		input->keyUp(KEY_PAGEDOWN);
		break;
	case SDLK_w:
		input->keyUp(KEY_W);
		break;
	case SDLK_a:
		input->keyUp(KEY_A);
		break;
	case SDLK_s:
		input->keyUp(KEY_S);
		break;
	case SDLK_d:
		input->keyUp(KEY_D);
		break;
	default:
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
		case WM_LBUTTONDOWN:
			_defaultCallback->getInput()->keyDown(BUTTON_LEFT);
			return 0;
		case WM_LBUTTONUP:
			_defaultCallback->getInput()->keyUp(BUTTON_LEFT);
			return 0;
		case WM_RBUTTONDOWN:
			_defaultCallback->getInput()->keyDown(BUTTON_RIGHT);
			return 0;
		case WM_RBUTTONUP:
			_defaultCallback->getInput()->keyUp(BUTTON_RIGHT);
			return 0;
		case WM_MOUSEMOVE:
			_defaultCallback->getInput()->mouseMove(LOWORD(lParam), HIWORD(lParam));
		default:
			return DefWindowProc( hwnd, Message, wParam, lParam );
	}
}
#endif

Input* Window::getInput()
{
	return this->input;
}

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
	// TODO: find out if this is actually keeping the same resolution
	/*glViewport(0, 0, (GLsizei)this->screenWidth, (GLsizei)this->screenHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// gluPerspective(45, (float)this->width/this->height, 0.1f, 100.0f);
	GLdouble aspectRatio = (GLdouble)this->screenWidth / (GLdouble)this->screenHeight;*/
	/*if(this->screenWidth <= this->screenHeight)
		glOrtho(-(this->resolutionWidth / 2), (this->resolutionWidth / 2),
				-(this->resolutionHeight / 2 / aspectRatio), (this->resolutionHeight / 2 / aspectRatio) / aspectRatio,
				this->resolutionDistance, -this->resolutionDistance);
	else
		glOrtho(-(this->resolutionWidth / 2 / aspectRatio), (this->resolutionWidth / 2 / aspectRatio)
				, -(this->resolutionHeight / 2), (this->resolutionHeight / 2), this->resolutionDistance, -this->resolutionDistance);*/
	/*gluPerspective( 45.0f, aspectRatio, 0.1f, this->resolutionDistance);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();*/
}

void Window::setRenderer(Renderer* newRenderer)
{
	this->renderer = newRenderer;
}

