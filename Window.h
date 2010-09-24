/* 
 * File:   Window.h
 * Author: scott
 *
 * Created on July 13, 2010, 10:30 PM
 */

#ifndef _WINDOW_H
#define	_WINDOW_H

#include <windows.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#ifdef __linux__
	#include <SDL/SDL.h>
#endif
// #include <SDL/SDL_opengl.h>

#include "Scene.h"
#include "Input.h"
#include "FrameRate.h"

class Window
{
public:
	// Create a window with default width/height
	Window();
	// Create a window with given width/height
	Window(int width, int height);
	virtual ~Window();

	// Initialize Window and start displaying
	void start(HINSTANCE program);
	// Calling thread waits for renderThread to exit
	void wait();
	// Make Window shutdown, close renderThread and eventsThread
	void quit();

	void setSize(int width, int height);
	void setResolution(GLdouble width, GLdouble height, GLdouble distance);

	// Set the scene to render
	void setScene(Scene* newScene);
	// Set the input mapping object
	void setInput(Input* input);
private:
	// Threads continue running while this is false
	bool terminate;

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
	void initWin();
	void initOpenGL();

	// Render scene, thread, and function
	FrameRate frameRate;
	Scene* renderScene;
	pthread_t renderThread;
	static void* renderLoop(void* arg);

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

		void keyDown(SDL_keysym* keysym);
		void keyUp(SDL_keysym* keysym);
	#endif

	void resetScreen();

	// width/height of the window
	int screenWidth;
	int screenHeight;

	// Resolution
	double resolutionWidth;
	double resolutionHeight;
	double resolutionDistance;
};

static Window* _defaultCallback;

#endif	/* _WINDOW_H */

