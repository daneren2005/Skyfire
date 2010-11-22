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

#include <iostream>

int BaseObject::objectIDCounter = 0;

BaseObject::BaseObject()
{
	this->objectID = BaseObject::objectIDCounter;
	BaseObject::objectIDCounter++;

	position = Vector(0.0f, 0.0f, 0.0f);
	angle = Vector(0.0f, 0.0f, 0.0f);
	camera = NULL;
	// mesh = NULL;
}
BaseObject::BaseObject(float x, float y, float z)
{
	this->objectID = BaseObject::objectIDCounter;
	BaseObject::objectIDCounter++;

	position = Vector(x, y, z);
	camera = NULL;
	// mesh = NULL;
}

BaseObject::BaseObject(const BaseObject& orig)
{
	objectID = orig.objectID;
	model = orig.model;
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
	Vector angle(this->angle[0], this->angle[1], this->angle[2]);
	Matrix4 rotate = Matrix4::rotateMovement(angle);
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
	this->angle = this->angle + vec;
	this->angle = this->angle % 360;
}
void BaseObject::rotateBy(const Vector& amount)
{
	this->rotateBy(amount[1], amount[0], amount[2]);
}

void BaseObject::transformObject()
{
	Matrix4 rotate = Matrix4::rotateObject(this->angle);
	Vector t(position[0], position[1], -position[2]);
	Matrix4 translate = Matrix4::translate(t);
	// Matrix4 transform = rotate * translate;
	// glMultMatrixf(transform.getMatrix());
	glMultMatrixf(rotate.getMatrix());
	glMultMatrixf(translate.getMatrix());
}
void BaseObject::transformCamera()
{
	if(this->camera == NULL)
	{
		Matrix4 rotate = Matrix4::rotateObject(!this->angle);
		Vector t(-position[0], -position[1], -position[2]);
		Matrix4 translate = Matrix4::translate(t);
		// Matrix4 transform = rotate * translate;
		// glMultMatrixf(transform.getMatrix());
		glMultMatrixf(rotate.getMatrix());
		glMultMatrixf(translate.getMatrix());
	}
	else
	{
		Vector r(angle[0] + camera->angle[0], -angle[1] + camera->angle[1], -angle[2] + camera->angle[2]);
		Matrix4 rotate = Matrix4::rotateObject(r);
		Vector t(-position[0] - camera->position[0], -position[1] - camera->position[1], -position[2] + camera->position[2]);
		Matrix4 translate = Matrix4::translate(t);
		// Matrix4 transform = rotate * translate;
		// glMultMatrixf(transform.getMatrix());
		glMultMatrixf(rotate.getMatrix());
		glMultMatrixf(translate.getMatrix());
	}
}

void BaseObject::draw(bool forceDraw)
{
	// Already drawn if camera is not null
	if(this->camera == NULL || forceDraw == true)
	{
		this->model.draw();
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
