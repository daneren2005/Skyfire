/* 
 * File:   RegionScene.cpp
 * Author: scott
 * 
 * Created on July 14, 2010, 8:21 PM
 */

#include "Camera.h"


#include <SDL/SDL.h>

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
	// SDL_WM_SetCaption("Window Title", "Icon Title");
	if(this->activeRegion)
		this->activeRegion->draw(this->position, this->angle);
}

void Camera::update(double update)
{
	
}

