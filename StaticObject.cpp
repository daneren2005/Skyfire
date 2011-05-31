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
	this->mesh = NULL;
}

StaticObject::StaticObject(float x, float y, float z) : BaseObject(x, y, z)
{
	this->mesh = NULL;
}

StaticObject::StaticObject(const StaticObject& orig) : BaseObject(orig)
{
	this->mesh = orig.mesh;
}

StaticObject::~StaticObject()
{
}

void StaticObject::draw()
{
	// Already drawn if camera is not null
	if(this->mesh == NULL)
	{
		return;
	}

	// this->getBoundingBox().draw();
	// this->mesh->getBoundingBox().getObjectOrientedBox().transform(position, directionForward).draw();
	// this->mesh->getBoundingBox().getSphere().transform(this->position).draw();

	// If in select mode, write object id to top of stack
	glLoadName(this->objectId());
	// Start a new matrix
	glPushMatrix();

	this->transform();

	// Draw then pop back down to old stack
	this->mesh->draw();
	glPopMatrix();
}

AxisAlignedBox StaticObject::getBoundingBox()
{
	return this->mesh->getBoundingBox().transform(this->position, this->directionForward);
}

