/* 
 * File:   StaticObject.cpp
 * Author: scott
 * 
 * Created on January 11, 2011, 1:17 PM
 */

#include "StaticObject.h"
#include "ObjectOrientedBox.h"
#include "Sphere.h"

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

	// this->getBoundingBox().draw();
	// this->model->getBoundingBox().getObjectOrientedBox().transform(position, directionForward).draw();
	// this->model->getBoundingBox().getSphere().transform(this->position).draw();

	// If in select mode, write object id to top of stack
	glLoadName(this->objectId());
	// Start a new matrix
	glPushMatrix();

	this->transform();

	// Draw then pop back down to old stack
	this->model->draw();
	glPopMatrix();
}

AxisAlignedBox StaticObject::getBoundingBox()
{
	return this->model->getBoundingBox().transform(this->position, this->directionForward);
}

