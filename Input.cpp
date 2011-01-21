/*
 * File:   Keyboard.cpp
 * Author: scott
 *
 * Created on July 14, 2010, 6:16 PM
 */

#include "Input.h"
#include "Console.h"

#ifdef WIN32
    #include <windows.h>
#endif

Input::Input()
{
	/*this->moveLeft = false;
	this->moveRight = false;
	this->moveUp = false;
	this->moveDown = false;
	this->moveIn = false;
	this->moveOut = false;
	this->rotateLeft = false;
	this->rotateRight = false;
	this->rotateUp = false;
	this->rotateDown = false;*/

	this->keys.insert(KEY_LEFT, Key(KEY_LEFT));
	this->keys.insert(KEY_RIGHT, Key(KEY_RIGHT));
}

Input::Input(const Input& orig)
{

}

Input::~Input()
{

}

void Input::keyDown(KeyType key)
{
	if(key == KEY_ESCAPE)
		exit(0);

	/*switch(key)
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
	}*/

	try
	{
		this->keys.search(key).keyDown();
	}
	catch(Exception& e)
	{
		Key pressed(key);
		pressed.keyDown();
		this->keys.insert(key, pressed);
	}
}
void Input::keyUp(KeyType key)
{
	try
	{
		this->keys.search(key).keyUp();
	}
	catch(Exception& e)
	{
		Key pressed(key);
		this->keys.insert(key, pressed);
	}

	/*switch(key)
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
	}*/
}

void Input::mouseMove(int x, int y)
{
	this->mouseX = x;
	this->mouseY = y;
}

bool Input::keyPressed(KeyType key)
{
	try
	{
		Key check = keys.search(key);
		if(check.keyPressed())
			return true;
		else
			return false;
	}
	catch(Exception& e)
	{
		console << "Test" << newline;
		return false;
	}
}
