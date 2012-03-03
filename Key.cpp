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
}
Key::Key(KeyType type)
{
	this->type = type;
	this->pressed = false;
}

Key::Key(const Key& orig)
{
	this->type = orig.type;
	this->pressed = orig.pressed;
	this->keyDownHandler = orig.keyDownHandler;
	this->keyPressHandler = orig.keyPressHandler;
	this->mouseDownHandler = orig.mouseDownHandler;
	this->mousePressHandler = orig.mousePressHandler;
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
	if(this->keyPressHandler.isSet())
	{
		this->keyPressHandler();
	}
	else if(this->mousePressHandler.isSet())
	{
		this->mousePressHandler(x, y);
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
	if(keyDownHandler.isSet())
	{
		this->keyDownHandler(interval);
	}
	else if(mouseDownHandler.isSet())
	{
		this->mouseDownHandler(interval, x, y);
	}
}

void Key::setKeyPressEventHandler(Function<void> eventHandler)
{
	this->keyPressHandler = eventHandler;
}
void Key::setKeyDownEventHandler(Function<void, double> eventHandler)
{
	this->keyDownHandler = eventHandler;
}

void Key::setMousePressEventHandler(Function<void, int, int> eventHandler)
{
	this->mousePressHandler = eventHandler;
}

void Key::setMouseDownEventHandler(Function<void, double, int, int> eventHandler)
{
	this->mouseDownHandler = eventHandler;
}

