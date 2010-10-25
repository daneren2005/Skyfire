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

void Camera::rotateBy(float x, float y, float z)
{
	BaseObject::rotateBy(x, -y, z);
}
void Camera::rotateBy(const Vector& amount) 
{
	BaseObject::rotateBy(amount[0], amount[1], amount[2]);
}

void Camera::setActiveObject(BaseObject* object)
{
	this->object = object;
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

	// Rotate camera around new origin
	Matrix4 rotate = Matrix4::rotateObject(!this->angle);
	glMultMatrixf(rotate.getMatrix());
	// Translate camera
	Matrix4 translate = Matrix4::translate(!this->position);
	glMultMatrixf(translate.getMatrix());

	glPushMatrix();

	if(this->activeRegion)
		this->activeRegion->draw();
}

void Camera::update(double update)
{

}

