/* 
 * File:   AnimateObject.cpp
 * Author: scott
 * 
 * Created on January 11, 2011, 1:05 PM
 */

#include "AnimateObject.h"

AnimateObject::AnimateObject() : BaseObject()
{
}

AnimateObject::AnimateObject(float x, float y, float z) : BaseObject(x, y, z)
{
	
}

AnimateObject::AnimateObject(const AnimateObject& orig) : BaseObject(orig)
{
}

AnimateObject::~AnimateObject()
{
}

