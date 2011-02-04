/*
 * File:   BaseObject.cpp
 * Author: scott
 *
 * Created on July 13, 2010, 8:20 PM
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

	position = Vector(0.0f, 0.0f, 0.0f);
	directionForward = Vector(0.0f, 0.0f, 0.0f);
	this->attachedCamera = NULL;
	this->parentRegion = NULL;
}
BaseObject::BaseObject(float x, float y, float z)
{
	this->objectID = BaseObject::objectIDCounter;
	BaseObject::objectIDCounter++;

	position = Vector(x, y, z);
	directionForward = Vector(0.0f, 0.0f, 0.0f);
	this->attachedCamera = NULL;
	this->parentRegion = NULL;
}

BaseObject::BaseObject(const BaseObject& orig)
{
	objectID = orig.objectID;
	this->position = orig.position;
	this->directionForward = orig.directionForward;
	this->attachedCamera = orig.attachedCamera;
	this->parentRegion = orig.parentRegion;
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

int BaseObject::objectId()
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

void BaseObject::transformObject()
{
	Matrix4 rotate = Matrix4::rotateObject(this->directionForward);
	Vector t(position[0], position[1], -position[2]);
	Matrix4 translate = Matrix4::translate(t);
	// Matrix4 transform = rotate * translate;
	// glMultMatrixf(transform.getMatrix());
	glMultMatrixf(translate.getMatrix());
	glMultMatrixf(rotate.getMatrix());
}
void BaseObject::transformCamera()
{
	if(this->attachedCamera == NULL)
	{
		Matrix4 rotate = Matrix4::rotateObject(!this->directionForward);
		Vector t(-position[0], -position[1], -position[2]);
		Matrix4 translate = Matrix4::translate(t);
		// Matrix4 transform = rotate * translate;
		// glMultMatrixf(transform.getMatrix());
		glMultMatrixf(rotate.getMatrix());
		glMultMatrixf(translate.getMatrix());
	}
	else
	{
		Vector r(directionForward[0] + attachedCamera->directionForward[0], -directionForward[1] + attachedCamera->directionForward[1], -directionForward[2] + attachedCamera->directionForward[2]);
		Matrix4 rotate = Matrix4::rotateObject(r);
		Vector t(-position[0] - attachedCamera->position[0], -position[1] - attachedCamera->position[1], -position[2] + attachedCamera->position[2]);
		Matrix4 translate = Matrix4::translate(t);
		// Matrix4 transform = rotate * translate;
		// glMultMatrixf(transform.getMatrix());
		glMultMatrixf(rotate.getMatrix());
		glMultMatrixf(translate.getMatrix());
	}
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
