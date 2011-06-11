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

#include "Key.h"

Key::Key()
{
	this->type = NULL_KEY;
	this->pressed = false;
	this->keyPressHandler = 0x0;
	this->keyPressArgs = 0x0;
	this->keyDownHandler = 0x0;
	this->keyDownArgs = 0x0;
	this->mousePressHandler = 0x0;
	this->mousePressArgs = 0x0;
	this->mouseDownHandler = 0x0;
	this->mouseDownArgs = 0x0;
}
Key::Key(KeyType type)
{
	this->type = type;
	this->pressed = false;
	this->keyPressHandler = 0x0;
	this->keyPressArgs = 0x0;
	this->keyDownHandler = 0x0;
	this->keyDownArgs = 0x0;
	this->mousePressHandler = 0x0;
	this->mousePressArgs = 0x0;
	this->mouseDownHandler = 0x0;
	this->mouseDownArgs = 0x0;
}

Key::Key(const Key& orig)
{
	this->type = orig.type;
	this->pressed = orig.pressed;
	// TODO: finish copy constructor
}

Key::~Key()
{
}

void Key::keyDown(int x, int y)
{
	this->pressed = true;
}
void Key::keyUp(int x , int y)
{
	this->pressed = false;
	if(this->keyPressHandler != 0x0)
	{
		this->keyPressHandler(this->keyPressArgs);
	}
	else if(this->mousePressHandler != 0x0)
	{
		this->mousePressHandler(this->mousePressArgs, x, y);
	}
}
bool Key::keyPressed()
{
	return this->pressed;
}

KeyType Key::keyType()
{
	return this->type;
}

bool Key::operator ==(const Key& rhs)
{
	if(this->type == rhs.type)
		return true;
	else
		return false;
}
bool Key::operator !=(const Key& rhs)
{
	if(this->type == rhs.type)
		return false;
	else
		return true;
}

void Key::update(double interval, int x, int y)
{
	if(keyDownHandler != 0x0)
	{
		this->keyDownHandler(this->keyDownArgs, interval);
	}
	else if(mouseDownHandler != 0x0)
	{
		this->mouseDownHandler(this->mouseDownArgs, interval, x, y);
	}
}

void Key::setKeyPressEventHandler(void*(*eventHandler)(void* args), void* args)
{
	this->keyPressHandler = eventHandler;
	this->keyPressArgs = args;
}
void Key::setKeyDownEventHandler(void*(*eventHandler)(void* args, double interval), void* args)
{
	this->keyDownHandler = eventHandler;
	this->keyDownArgs = args;
}

void Key::setMousePressEventHandler(void*(*eventHandler)(void* args, int x, int y), void* args)
{
	this->mousePressHandler = eventHandler;
	this->mousePressArgs = args;
}

void Key::setMouseDownEventHandler(void*(*eventHandler)(void* args, double interval, int x, int y), void* args)
{
	this->mouseDownHandler = eventHandler;
	this->mouseDownArgs = args;
}

