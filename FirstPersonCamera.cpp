/* 
 * File:   FirstPersonCamera.cpp
 * Author: scott
 * 
 * Created on July 15, 2011, 7:05 PM
 */

#include "FirstPersonCamera.h"

FirstPersonCamera::FirstPersonCamera()
{
    this->object = NULL;
}

FirstPersonCamera::FirstPersonCamera(const FirstPersonCamera& orig)
{
    this->object = orig.object;
}

FirstPersonCamera::~FirstPersonCamera()
{
}

void FirstPersonCamera::attachTo(BaseObject* object)
{
	this->object = object;
	this->object->setAttachedCamera(this);
}
void FirstPersonCamera::detach()
{
	this->object->setAttachedCamera(NULL);
	this->object = NULL;
}

