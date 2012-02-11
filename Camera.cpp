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
#include <float.h>

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

Vector Camera::projectMouseBack(int x, int y)
{
	GLdouble model_view[16];
	GLint viewport[4];
	GLdouble projection[16];

	GLfloat winX, winY, winZ;
	GLdouble dx, dy, dz;

	glGetDoublev(GL_MODELVIEW_MATRIX, model_view);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);

	winX = (float)x;
	winY = (float)viewport[3] - (float)y;

	glReadPixels ((int)x, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ); 
	gluUnProject(winX, winY, 1, model_view, projection, viewport, &dx, &dy, &dz);

	return Vector(dx, -dy, dz);
}
Ray Camera::projectMouseRay(int x, int y)
{
	GLdouble model_view[16];
	GLint viewport[4];
	GLdouble projection[16];

	GLfloat winX, winY, winZ;
	GLdouble dx, dy, dz, bx, by, bz;

	glGetDoublev(GL_MODELVIEW_MATRIX, model_view);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);

	winX = (float)x;
	winY = (float)viewport[3] - (float)y;

	glReadPixels ((int)x, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ); 
	gluUnProject(winX, winY, 0, model_view, projection, viewport, &bx, &by, &bz);
	gluUnProject(winX, winY, 1, model_view, projection, viewport, &dx, &dy, &dz);

	return Ray(Vector(bx, by, bz), Vector(dx, -dy, dz));
}

BaseObject* Camera::getObjectAt(int x, int y)
{
	if(activeRegion == 0x0)
		return 0x0;
	
	// Projection of point
	Ray ray = projectMouseRay(x, y);
	console << ray << newline;
	
	// Farthest out the point could have hit
	float minT = FLT_MAX;
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
