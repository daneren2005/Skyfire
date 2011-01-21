/* 
 * File:   Key.cpp
 * Author: scott
 * 
 * Created on July 20, 2010, 8:06 PM
 */

#include "Key.h"

Key::Key()
{
	this->type = NULL_KEY;
	this->pressed = false;
	this->eventHandler = 0x0;
}
Key::Key(KeyType type)
{
	this->type = type;
	this->pressed = false;
	this->eventHandler = 0x0;
}

Key::Key(const Key& orig)
{
	this->type = orig.type;
	this->pressed = orig.pressed;
	this->eventHandler = orig.eventHandler;
}

Key::~Key()
{
}

void Key::keyDown()
{
	this->pressed = true;
}
void Key::keyUp()
{
	this->pressed = false;
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

void Key::setEventHandler(void*(*eventHandler)())
{
	this->eventHandler = eventHandler;
}

