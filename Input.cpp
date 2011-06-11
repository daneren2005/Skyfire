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

#include "Input.h"
#include "Console.h"

#ifdef WIN32
    #include <windows.h>
#endif

Input::Input()
{
	this->mouseHandler = 0x0;
	this->mouseArgs = 0x0;

	this->keys.insert(KEY_LEFT, new Key(KEY_LEFT));
	this->keys.insert(KEY_RIGHT, new Key(KEY_RIGHT));

	this->mouseX = 0;
	this->mouseY = 0;
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

	try
	{
		this->keys.search(key)->keyDown(this->mouseX, this->mouseY);
	}
	catch(Exception& e)
	{
		Key* pressed = new Key(key);
		pressed->keyDown();
		this->keys.insert(key, pressed);
	}
}
void Input::keyUp(KeyType key)
{
	try
	{
		this->keys.search(key)->keyUp(this->mouseX, this->mouseY);
	}
	catch(Exception& e)
	{
		Key* pressed = new Key(key);
		this->keys.insert(key, pressed);
	}
}

void Input::mouseMove(int x, int y)
{
	this->mouseX = x;
	this->mouseY = y;

	if(this->mouseHandler != 0x0)
	{
		this->mouseHandler(this->mouseArgs, this->mouseX, this->mouseY);
	}
}

bool Input::keyPressed(KeyType key)
{
	try
	{
		Key* check = keys.search(key);
		if(check->keyPressed())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	catch(Exception& e)
	{
		return false;
	}
}

int Input::mouseLocationX()
{
	return this->mouseX;
}
int Input::mouseLocationY()
{
	return this->mouseY;
}

void Input::setMousePressEventHandler(KeyType key, void*(*eventHandler)(void* args, int x, int y), void* args)
{
	try
	{
		this->keys.search(key)->setMousePressEventHandler(eventHandler, args);
	}
	catch(Exception& e)
	{
		Key* pressed = new Key(key);
		pressed->setMousePressEventHandler(eventHandler, args);
		this->keys.insert(key, pressed);
	}
}
void Input::setMouseDownEventHandler(KeyType key, void*(*eventHandler)(void* args, double interval, int x, int y), void* args)
{
	try
	{
		this->keys.search(key)->setMouseDownEventHandler(eventHandler, args);
	}
	catch(Exception& e)
	{
		Key* pressed = new Key(key);
		pressed->setMouseDownEventHandler(eventHandler, args);
		this->keys.insert(key, pressed);
	}
}
void Input::setMouseMoveEventHandler(void*(*eventHandler)(void* args, int x, int y), void* args)
{
	this->mouseHandler = eventHandler;
	this->mouseArgs = args;
}

void Input::setKeyPressEventHandler(KeyType key, void*(*eventHandler)(void* args), void* args)
{
	try
	{
		this->keys.search(key)->setKeyPressEventHandler(eventHandler, args);
	}
	catch(Exception& e)
	{
		Key* pressed = new Key(key);
		pressed->setKeyPressEventHandler(eventHandler, args);
		this->keys.insert(key, pressed);
	}
}
void Input::setKeyDownEventHandler(KeyType key, void*(*eventHandler)(void* args, double interval), void* args)
{
	try
	{
		this->keys.search(key)->setKeyDownEventHandler(eventHandler, args);
	}
	catch(Exception& e)
	{
		Key* pressed = new Key(key);
		pressed->setKeyDownEventHandler(eventHandler, args);
		this->keys.insert(key, pressed);
	}
}

void Input::update(double interval)
{
	for(Map<KeyType, Key*>::Iterator it = this->keys.begin(); !it; it++)
	{
		if(it.value()->keyPressed())
		{
			it.value()->update(interval, this->mouseX, this->mouseY);
		}
	}
}
