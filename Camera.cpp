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

	position = Vector();
	angle = Vector();
}

Camera::Camera(const Camera& orig)
{

}

Camera::~Camera()
{

}

void Camera::setActiveRegion(Region* region)
{
	this->activeRegion = region;
}

void Camera::render()
{
	glLoadIdentity();

	// Rotate camera around new origin
	Matrix4 rotate = Matrix4::rotate(!this->angle);
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

