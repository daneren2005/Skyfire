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

#include <GL/glu.h>

#include <iostream>
#include <cmath>
#include <float.h>

Camera::Camera() : Renderer()
{
	this->activeRegion = NULL;

	this->position = Vector(0.0f, 0.0f, 0.0f);
	this->direction = Vector(0.0f, 0.0f, 0.0f);
}

Camera::Camera(const Camera& orig) : Renderer(orig)
{
    this->activeRegion = orig.activeRegion;
    this->position = orig.position;
    this->direction = orig.direction;
}

Camera::~Camera()
{

}

void Camera::render()
{	
	this->viewport2D();
	this->renderHUD();
	this->viewport3D();

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
	this->transform();

	if(this->activeRegion)
		this->activeRegion->draw();
}
void Camera::renderHUD()
{
	glTranslatef(0.0f,0.0f,-1.0f);
	
	glColor3f(1.0f, 0.0f, 0.0f);
	glRasterPos2i(200, 200);
	glPushAttrib(GL_LIST_BIT);
	glCallLists(13, GL_UNSIGNED_BYTE, "OpenGL Rocks!");
}

void Camera::setActiveRegion(Region* region)
{
	this->activeRegion = region;
}
Region* Camera::getActiveRegion()
{
	return this->activeRegion;
}

void Camera::moveBy(float x, float y, float z)
{
	Vector amount(x, y, z);
	this->moveBy(amount);
}
void Camera::moveBy(const Vector& amount)
{
	this->position = this->position + amount;
}
void Camera::moveByDirection(float x, float y, float z)
{
	Vector amount(x, y, z);
	this->moveByDirection(amount);
}
void Camera::moveByDirection(const Vector& amount)
{
	Vector directionForward(this->direction[0], this->direction[1], this->direction[2]);
	Matrix4 rotate = Matrix4::rotateMovement(directionForward);
	Vector move = rotate * amount;

	this->position = this->position + move;
}
void Camera::moveTo(float x, float y, float z)
{
	this->position = Vector(x, y, z);
}
void Camera::moveTo(const Vector& amount)
{
	this->position = amount;
}
void Camera::rotateBy(float x, float y, float z)
{
	Vector vec(-y, x, z);
	this->direction = this->direction + vec;
	this->direction = this->direction % 360;
}
void Camera::rotateBy(const Vector& amount)
{
	this->rotateBy(-amount[1], amount[0], amount[2]);
}
void Camera::rotateTo(float x, float y, float z)
{
	this->direction = Vector(y, x, z);
}
void Camera::rotateTo(const Vector& amount)
{
	this->direction = Vector(amount[1], amount[0], amount[2]);
}

void Camera::transform()
{
	Matrix4 rotate = Matrix4::rotateObject(!this->direction);
	Vector t(-position[0], -position[1], -position[2]);
	Matrix4 translate = Matrix4::translate(t);

	glMultMatrixf(rotate.getMatrix());
	glMultMatrixf(translate.getMatrix());
}
Matrix4 Camera::getTransform()
{
	Matrix4 rotate = Matrix4::rotateObject(this->direction);
	Vector t(position[0], position[1], -position[2]);
	Matrix4 translate = Matrix4::translate(t);
	
	Matrix4 transform = rotate * translate;
	return transform;
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
