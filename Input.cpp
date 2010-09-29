/*
 * File:   Keyboard.cpp
 * Author: scott
 *
 * Created on July 14, 2010, 6:16 PM
 */

#include "Input.h"

#ifdef WIN32
    #include <windows.h>
#endif

Input::Input()
{
	this->moveLeft = false;
	this->moveRight = false;
	this->moveUp = false;
	this->moveDown = false;
	this->moveIn = false;
	this->moveOut = false;
	this->rotateLeft = false;
	this->rotateRight = false;
	this->rotateUp = false;
	this->rotateDown = false;
}

Input::Input(const Input& orig)
{

}

Input::~Input()
{

}

void Input::keyDown(KeyType key)
{
	switch(key)
	{
	case KEY_ESCAPE:
		exit(0);
		break;
	case KEY_UP:
		this->moveUp = true;
		break;
	case KEY_DOWN:
		this->moveDown = true;
		break;
	case KEY_LEFT:
		this->moveLeft = true;
		break;
	case KEY_RIGHT:
		this->moveRight = true;
		break;
	case KEY_PAGEUP:
		this->moveIn = true;
		break;
	case KEY_PAGEDOWN:
		this->moveOut = true;
		break;
	case KEY_A:
		this->rotateLeft = true;
		break;
	case KEY_S:
		this->rotateDown = true;
		break;
	case KEY_D:
		this->rotateRight = true;
		break;
	case KEY_W:
		this->rotateUp = true;
		break;
	}
}
void Input::keyUp(KeyType key)
{
	switch(key)
	{
	case KEY_ESCAPE:
		exit(0);
		break;
	case KEY_UP:
		this->moveUp = false;
		break;
	case KEY_DOWN:
		this->moveDown = false;
		break;
	case KEY_LEFT:
		this->moveLeft = false;
		break;
	case KEY_RIGHT:
		this->moveRight = false;
		break;
	case KEY_PAGEUP:
		this->moveIn = false;
		break;
	case KEY_PAGEDOWN:
		this->moveOut = false;
		break;
	case KEY_A:
		this->rotateLeft = false;
		break;
	case KEY_S:
		this->rotateDown = false;
		break;
	case KEY_D:
		this->rotateRight = false;
		break;
	case KEY_W:
		this->rotateUp = false;
		break;
	}
}

bool Input::keyPressed(Key key)
{
	return false;
}
