#pragma once

#include <skyfire.h>
#include <windows.h>

class Application
{
private:
	HINSTANCE program;

	Input input;
public:
	Application(HINSTANCE program);
	~Application(void);
};
