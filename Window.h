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

#ifndef _WINDOW_H
#define	_WINDOW_H

#ifdef WIN32
	#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>

#ifdef __linux__
	#include <SDL/SDL.h>
#endif

#include "Renderer.h"
#include "Input.h"
#include "Thread.h"
#include "Font2D.h"

class Window
{
public:
	Window();
	Window(int width, int height);
	virtual ~Window();

	// Calling thread waits for renderThread to exit
	void wait();
	void quit();

	void setSize(int width, int height);
	void setRenderer(Renderer* newRenderer);
	
	Font2D getDefaultFont();
	void setDefaultFont(Font2D font);
private:
	// width/height of the window
	int screenWidth;
	int screenHeight;

	// Initilization of Window
	#ifdef WIN32
		HINSTANCE programHandle;
		HWND winHandle;
		HDC device;
		HGLRC render;
	#endif
	#ifdef __linux__
		int videoFlags;
		SDL_Surface* surface;
	#endif

	Font2D font;
	friend class Font2D;

	void initWin(Thread* arg);
	void initDefaultFont();
	void initOpenGL();

	// Render scene, thread, and function
	Renderer* renderer;
	Thread renderThread;
	Thread inputThread;
	void renderFunction(Thread* arg);
	void inputFunction(Thread* arg);

	// Events thread, loop function, and processing function
	Input* input;
	#ifdef WIN32
		// Default callback
		static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

		void keyDown(int key);
		void keyUp(int key);
	#endif
	#ifdef __linux__
		virtual void processEvent(SDL_Event* event);

		void mouseMove(int x, int y);
		void mouseDown(int button);
		void mouseUp(int button);
		void keyDown(SDL_keysym* keysym);
		void keyUp(SDL_keysym* keysym);
	#endif
};

#ifdef WIN32
	extern Window* _defaultCallback;
#endif

#endif	/* _WINDOW_H */

