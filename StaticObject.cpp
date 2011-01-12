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
	else if(this->camera == NULL)
	{
		glPushMatrix();
		this->transformObject();
		this->model->draw();
		glPopMatrix();
	}
	else
	{
		glPushMatrix();
		this->camera->transformCamera();
		this->model->draw();
		glPopMatrix();
	}
}

