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

