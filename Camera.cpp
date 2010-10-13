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

	Matrix4 m = Matrix4::translate(this->position);
	/*std::cout << arr[0] << std::endl;
	std::cout << arr[4] << std::endl;
	std::cout << arr[5] << std::endl;
	std::cout << arr[15] << std::endl;*/
	glMultMatrixf(m.getMatrix());
	glPushMatrix();

	if(this->activeRegion)
		this->activeRegion->draw();
}

void Camera::update(double update)
{

}

