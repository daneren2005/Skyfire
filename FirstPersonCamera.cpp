/* 
 * File:   FirstPersonCamera.cpp
 * Author: scott
 * 
 * Created on July 15, 2011, 7:05 PM
 */

#include "FirstPersonCamera.h"

FirstPersonCamera::FirstPersonCamera()
{
    this->object = NULL;
}

FirstPersonCamera::FirstPersonCamera(const FirstPersonCamera& orig)
{
    this->object = orig.object;
}

FirstPersonCamera::~FirstPersonCamera()
{
}

void FirstPersonCamera::attachTo(BaseObject* object)
{
	this->object = object;
	this->object->setAttachedCamera(this);
}
void FirstPersonCamera::detach()
{
	this->object->setAttachedCamera(NULL);
	this->object = NULL;
}

void FirstPersonCamera::moveBy(float x, float y, float z)
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
void FirstPersonCamera::moveBy(const Vector& amount)
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
void FirstPersonCamera::moveByDirection(float x, float y, float z)
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
void FirstPersonCamera::moveByDirection(const Vector& amount)
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
void FirstPersonCamera::moveTo(float x, float y, float z)
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
void FirstPersonCamera::moveTo(const Vector& amount)
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

void FirstPersonCamera::rotateBy(float x, float y, float z)
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
void FirstPersonCamera::rotateBy(const Vector& amount) 
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

void FirstPersonCamera::draw()
{
	glLoadIdentity();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);

	// Setup light for scene
	float lightAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};
	glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);
	float lightSpec[] = {0.9f, 0.9f, 0.9f, 1.0f};
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpec);
	float lightDiff[] = {1.0f, 1.0f, 1.0f, 1.0f};
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiff);
	float lightPos[] = {0.0f, 0.0f, 10.0f, 1.0f};
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos);

	// If a base object exists, transform on it as well
	this->transformInverse();

	if(this->activeRegion)
		this->activeRegion->draw();
}

