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

