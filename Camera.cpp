/*
 * File:   RegionScene.cpp
 * Author: scott
 *
 * Created on July 14, 2010, 8:21 PM
 */

#include "Camera.h"

#include <SDL/SDL.h>
#include <GL/glu.h>

#include <iostream>

Camera::Camera() : Scene()
{
	this->activeRegion = NULL;
	this->object = NULL;

	position = Vector();
	directionForward = Vector();
}

Camera::Camera(const Camera& orig) : Scene(orig)
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
	this->object->setAttachedCamera(this);
}
void Camera::detach()
{
	this->object->setAttachedCamera(NULL);
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

void Camera::draw()
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

void Camera::update(double update)
{

}


void Camera::load()
{
	
}

BaseObject* Camera::getObjectAt(int x, int y)
{
	unsigned int buffer[64];
	int hits, view[4];
	int id;

	// Setup Select mode
	glSelectBuffer(64, buffer);
	glGetIntegerv(GL_VIEWPORT, view);
	glRenderMode(GL_SELECT);

	// Init select mode
	glInitNames();
	glPushName(0);

	// Run draw to get the objects
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
		glLoadIdentity();
		gluPickMatrix(x, view[3] - y, 1.0f, 1.0f, view);
		// TODO: get angle + viewing distances from window settings, not hard coded
		gluPerspective(45.0f, (GLfloat) (view[2]-view[0])/(GLfloat) (view[3]-view[1]), 0.1f, 100.0f);

		glMatrixMode(GL_MODELVIEW);
		this->render();
		glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	hits = glRenderMode(GL_RENDER);

	int maxId = 0;
	int maxValue = -1;
	for(int i = 0; i < hits; i++)
	{
		if(buffer[i * 4 + 1] < maxValue || maxValue == -1)
		{
			maxId = buffer[i * 4 + 3];
			maxValue = buffer[i * 4 + 1];
		}
	}

	if(maxId != 0)
	{
		for(List<BaseObject*>::Iterator it = this->activeRegion->objects.begin(); !it; it++)
		{
			if(it.value()->objectId() == maxId)
			{
				return it.value();
			}
		}
	}
	
	return 0x0;
}

Array<BaseObject*> Camera::getOBjectsIn(int x, int y, int width, int height)
{
	Array<BaseObject*> temp;
	return temp;
}
