/* 
 * File:   StaticObject.cpp
 * Author: scott
 * 
 * Created on January 11, 2011, 1:17 PM
 */

#include "StaticObject.h"

StaticObject::StaticObject() : BaseObject()
{
	this->model = NULL;
}

StaticObject::StaticObject(float x, float y, float z) : BaseObject(x, y, z)
{
	this->model = NULL;
}

StaticObject::StaticObject(const StaticObject& orig) : BaseObject(orig)
{
	this->model = orig.model;
}

StaticObject::~StaticObject()
{
}

void StaticObject::draw()
{
	// Already drawn if camera is not null
	if(this->model == NULL)
	{
		return;
	}

	// If in select mode, write object id to top of stack
	glLoadName(this->objectId());
	// Start a new matrix
	glPushMatrix();

	// Transform scene based on wether object is attached to camera or not
	if(this->camera == NULL)
	{
		this->transformObject();
	}
	else
	{
		this->camera->transformCamera();
	}

	// Draw then pop back down to old stack
	this->model->draw();
	glPopMatrix();
}

