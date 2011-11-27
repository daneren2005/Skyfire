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

#include "Camera.h"

#include <SDL/SDL.h>
#include <GL/glu.h>

#include <iostream>
#include <cmath>

Camera::Camera() : BaseObject()
{
	this->activeRegion = NULL;

	position = Vector();
	directionForward = Vector();
}

Camera::Camera(const Camera& orig) : BaseObject(orig)
{
    this->activeRegion = orig.activeRegion;
    this->position = orig.position;
    this->directionForward = orig.directionForward;
}

Camera::~Camera()
{

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
	if(activeRegion == 0x0)
		return 0x0;
	
	int width2 = 1280 / 2;
	int height2 = 720 / 2;
	float z = height2 / tan(M_PI/8.0f);
	
	// Projection of point
	Ray ray(Vector(), Vector(float(x - width2) + 0.5f, float(height2 - y) + 0.5f, -z));
	console << ray << newline;
	Vector s;
	Vector r(float(x - width2) + 0.5f, float(y - height2) + 0.5f, -z);
	
	// Transform points to world coordinates
	Matrix4 transform = this->getTransform();
	s = transform * s;
	r = transform * s;
	
	// Farthest out the point could have hit
	float minT = 100000.0f;
	
	BaseObject* object = 0x0;
	
	for(List<BaseObject*>::Iterator it = activeRegion->objects.begin(); !it; it++)
	{
		ModelPointer model = it.value()->getModel();
		if(model == 0x0)
			continue;
		
		// float t = model->getRayIntersection(s, r);
		Matrix4 objectTransform = it.value()->getTransform();
		float t = model->getRayIntersection(ray, objectTransform);
		console << t << newline;
		if(t > 0.0f && t < minT)
			return it.value();
	}
	
	return object;
}

Array<BaseObject*> Camera::getOBjectsIn(int x, int y, int width, int height)
{
	Array<BaseObject*> temp;
	return temp;
}
