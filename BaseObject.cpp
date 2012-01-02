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

#include "BaseObject.h"

// #include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include "const.h"
#include <cmath>

#include "Camera.h"
#include "Region.h"

#include <iostream>

int BaseObject::objectIDCounter = 1;

BaseObject::BaseObject()
{
	this->objectID = BaseObject::objectIDCounter;
	BaseObject::objectIDCounter++;

	this->model = NULL;
	position = Vector(0.0f, 0.0f, 0.0f);
	directionForward = Vector(0.0f, 0.0f, 0.0f);
	this->scale = Vector(1.0f, 1.0f, 1.0f);
	this->attachedCamera = NULL;
	this->parentRegion = NULL;
}
BaseObject::BaseObject(float x, float y, float z)
{
	this->objectID = BaseObject::objectIDCounter;
	BaseObject::objectIDCounter++;

	this->model = NULL;
	position = Vector(x, y, z);
	directionForward = Vector(0.0f, 0.0f, 0.0f);
	this->scale = Vector(1.0f, 1.0f, 1.0f);
	this->attachedCamera = NULL;
	this->parentRegion = NULL;
}

BaseObject::BaseObject(const BaseObject& orig)
{
	this->model = orig.model;
	objectID = orig.objectID;
	this->position = orig.position;
	this->directionForward = orig.directionForward;
	this->attachedCamera = orig.attachedCamera;
	this->parentRegion = orig.parentRegion;
	this->scale = orig.scale;
}

BaseObject::~BaseObject()
{
}

void BaseObject::moveBy(float x, float y, float z)
{
	Vector amount(x, y, z);
	this->moveBy(amount);
}
void BaseObject::moveBy(const Vector& amount)
{
	this->position = this->position + amount;
}
void BaseObject::moveByDirection(float x, float y, float z)
{
	Vector amount(x, y, z);
	this->moveByDirection(amount);
}
void BaseObject::moveByDirection(const Vector& amount)
{
	Vector directionForward(this->directionForward[0], this->directionForward[1], this->directionForward[2]);
	Matrix4 rotate = Matrix4::rotateMovement(directionForward);
	Vector move = rotate * amount;

	this->position = this->position + move;
}
void BaseObject::moveTo(float x, float y, float z)
{
	this->position = Vector(x, y, z);
}
void BaseObject::moveTo(const Vector& amount)
{
	this->position = amount;
}
void BaseObject::rotateBy(float x, float y, float z)
{
	Vector vec(y, x, z);
	this->directionForward = this->directionForward + vec;
	this->directionForward = this->directionForward % 360;
}
void BaseObject::rotateBy(const Vector& amount)
{
	this->rotateBy(amount[1], amount[0], amount[2]);
}

int BaseObject::getObjectId()
{
	return this->objectID;
}
Vector BaseObject::getPosition()
{
	return this->position;
}
Vector BaseObject::getAngle()
{
	return this->directionForward;
}
Camera* BaseObject::getAttachedCamera()
{
	return this->attachedCamera;
}
void BaseObject::setAttachedCamera(Camera* camera)
{
	this->attachedCamera = camera;
}
Region* BaseObject::getParentRegion()
{
	return this->parentRegion;
}
void BaseObject::setParentRegion(Region* region)
{
	this->parentRegion = region;
}
void BaseObject::setModel(ModelPointer model)
{
	this->model = model;
}
ModelPointer BaseObject::getModel()
{
	return model;
}

void BaseObject::transform()
{
	Matrix4 rotate = Matrix4::rotateObject(this->directionForward);
	Vector t(position[0], position[1], -position[2]);
	Matrix4 translate = Matrix4::translate(t);
	Matrix4 scale = Matrix4::scale(this->scale);
	// Matrix4 transform = rotate * translate;
	// glMultMatrixf(transform.getMatrix());
	glMultMatrixf(translate.getMatrix());
	glMultMatrixf(rotate.getMatrix());
	glMultMatrixf(scale.getMatrix());
}
Matrix4 BaseObject::getTransform()
{
	Matrix4 rotate = Matrix4::rotateObject(this->directionForward);
	Vector t(position[0], position[1], -position[2]);
	Matrix4 translate = Matrix4::translate(t);
	Matrix4 scale = Matrix4::scale(this->scale);
	
	Matrix4 transform = translate * rotate;
	transform = transform * scale;
	return transform;
}
void BaseObject::transformInverse()
{
	Matrix4 rotate = Matrix4::rotateObject(!this->directionForward);
	Vector t(-position[0], -position[1], -position[2]);
	Matrix4 translate = Matrix4::translate(t);
	Matrix4 scale = Matrix4::scale(Vector(1.0f / this->scale[0], 1.0f / this->scale[1], 1.0f / this->scale[2]));
	// Matrix4 transform = rotate * translate;
	// glMultMatrixf(transform.getMatrix());
	glMultMatrixf(scale.getMatrix());
	glMultMatrixf(rotate.getMatrix());
	glMultMatrixf(translate.getMatrix());
}
Matrix4 BaseObject::getTransformInverse()
{
	Matrix4 rotate = Matrix4::rotateObject(this->directionForward);
	Vector t(position[0], position[1], -position[2]);
	Matrix4 translate = Matrix4::translate(t);
	Matrix4 scale = Matrix4::scale(this->scale);
	
	Matrix4 transform = scale * rotate;
	transform = transform * translate;
	return transform;
}

void BaseObject::draw()
{
	// Already drawn if camera is not null
	if(this->model == NULL)
	{
		return;
	}

	this->getBoundingBox().draw();
	// this->model->getBoundingBox().getObjectOrientedBox().transform(position, directionForward).draw();
	// this->model->getBoundingBox().getSphere().transform(this->position).draw();

	// Start a new matrix
	glPushMatrix();

	this->transform();

	// Draw then pop back down to old stack
	this->model->draw();
	glPopMatrix();
}

void BaseObject::load()
{
	
}
void BaseObject::load(DataFile::Object* unit, DataFile::Object* obj)
{
	
}

AxisAlignedBox BaseObject::getBoundingBox()
{
	return this->model->getBoundingBox().transform(this->position, this->directionForward);
}

bool BaseObject::operator==(const BaseObject& rhs)
{
	if(this->objectID == rhs.objectID)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool BaseObject::operator!=(const BaseObject& rhs)
{
	if(this->objectID == rhs.objectID)
	{
		return false;
	}
	else
	{
		return true;
	}
}
