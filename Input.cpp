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
	this->mouseX = 0;
	this->mouseY = 0;
}

Input::Input(const Input& orig)
{
	this->mouseX = orig.mouseX;
	this->mouseY = orig.mouseY;
	this->mouseHandler = orig.mouseHandler;
	this->keys = orig.keys;
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
		this->keys.insert(pressed, key);
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
		this->keys.insert(pressed, key);
	}
}

void Input::mouseMove(int x, int y)
{
	this->mouseX = x;
	this->mouseY = y;

	if(this->mouseHandler.isSet())
	{
		this->mouseHandler(this->mouseX, this->mouseY);
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

void Input::setMousePressEventHandler(KeyType key, Function<void, int, int> eventHandler)
{
	try
	{
		this->keys.search(key)->setMousePressEventHandler(eventHandler);
	}
	catch(Exception& e)
	{
		Key* pressed = new Key(key);
		pressed->setMousePressEventHandler(eventHandler);
		this->keys.insert(pressed, key);
	}
}
void Input::setMouseDownEventHandler(KeyType key, Function<void, double, int, int> eventHandler)
{
	try
	{
		this->keys.search(key)->setMouseDownEventHandler(eventHandler);
	}
	catch(Exception& e)
	{
		Key* pressed = new Key(key);
		pressed->setMouseDownEventHandler(eventHandler);
		this->keys.insert(pressed, key);
	}
}
void Input::setMouseMoveEventHandler(Function<void, int, int> eventHandler)
{
	this->mouseHandler = eventHandler;
}

void Input::setKeyPressEventHandler(KeyType key, Function<void> eventHandler)
{
	try
	{
		this->keys.search(key)->setKeyPressEventHandler(eventHandler);
	}
	catch(Exception& e)
	{
		Key* pressed = new Key(key);
		pressed->setKeyPressEventHandler(eventHandler);
		this->keys.insert(pressed, key);
	}
}
void Input::setKeyDownEventHandler(KeyType key, Function<void, double> eventHandler)
{
	try
	{
		this->keys.search(key)->setKeyDownEventHandler(eventHandler);
	}
	catch(Exception& e)
	{
		Key* pressed = new Key(key);
		pressed->setKeyDownEventHandler(eventHandler);
		this->keys.insert(pressed, key);
	}
}

void Input::update(double interval)
{
	for(Map<Key*, KeyType>::Iterator it = this->keys.begin(); !it; it++)
	{
		if(it.value()->keyPressed())
		{
			it.value()->update(interval, this->mouseX, this->mouseY);
		}
	}
}
