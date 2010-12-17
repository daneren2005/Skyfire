/*
 * File:   RegionScene.cpp
 * Author: scott
 *
 * Created on July 14, 2010, 8:21 PM
 */

#include "Camera.h"

#include <SDL/SDL.h>

#include <iostream>

Camera::Camera()
{
	this->activeRegion = NULL;
	this->object = NULL;

	position = Vector();
	angle = Vector();
}

Camera::Camera(const Camera& orig)
{

}

Camera::~Camera()
{

}

void Camera::moveBy(float x, float y, float z)
{
	if(this->object != NULL)
	{
		this->object->moveBy(x, y, z);
	}
	else
	{
		BaseObject::moveBy(x, y, z);
	}
}
void Camera::moveBy(const Vector& amount)
{
	if(this->object != NULL)
	{
		this->object->moveBy(amount);
	}
	else
	{
		BaseObject::moveBy(amount);
	}
}
void Camera::moveByDirection(float x, float y, float z)
{
	if(this->object != NULL)
	{
		this->object->moveByDirection(x, y, z);
	}
	else
	{
		BaseObject::moveByDirection(x, y, z);
	}
}
void Camera::moveByDirection(const Vector& amount)
{
	if(this->object != NULL)
	{
		this->object->moveByDirection(amount);
	}
	else
	{
		BaseObject::moveByDirection(amount);
	}
}
void Camera::moveTo(float x, float y, float z)
{
	if(this->object != NULL)
	{
		this->object->moveTo(x, y, z);
	}
	else
	{
		BaseObject::moveTo(x, y, z);
	}
}
void Camera::moveTo(const Vector& amount)
{
	if(this->object != NULL)
	{
		this->object->moveTo(amount);
	}
	else
	{
		BaseObject::moveTo(amount);
	}
}

void Camera::rotateBy(float x, float y, float z)
{
	if(this->object != NULL)
	{
		this->object->rotateBy(x, y, z);
	}
	else
	{
		BaseObject::rotateBy(x, -y, z);
	}
}
void Camera::rotateBy(const Vector& amount) 
{
	if(this->object != NULL)
	{
		this->object->rotateBy(amount);
	}
	else
	{
		BaseObject::rotateBy(amount[0], -amount[1], amount[2]);
	}
}

void Camera::attachTo(BaseObject* object)
{
	this->object = object;
	this->object->camera = this;
}
void Camera::detach()
{
	this->object->camera = NULL;
	this->object = NULL;
}

void Camera::setActiveRegion(Region* region)
{
	this->activeRegion = region;
}
Region* Camera::getActiveRegion()
{
	return this->activeRegion;
}

void Camera::render()
{
	glLoadIdentity();

	// If a base object exists, transform on it as well
	if(this->object != NULL)
	{
		this->object->draw();
		this->object->transformCamera();
	}

	if(this->activeRegion)
		this->activeRegion->draw();
}

void Camera::update(double update)
{

}


void Camera::load()
{
	
}
