/* 
 * File:   Key.cpp
 * Author: scott
 * 
 * Created on July 20, 2010, 8:06 PM
 */

#include "Key.h"

Key::Key(KeyType type)
{
	this->type = type;
}

Key::Key(const Key& orig)
{
}

Key::~Key()
{
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

