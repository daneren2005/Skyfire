/* 
 * File:   Sphere.cpp
 * Author: scott
 * 
 * Created on May 8, 2011, 12:56 AM
 */

#include "Sphere.h"
#include "AxisAlignedBox.h"
#include "ObjectOrientedBox.h"

#include <stdlib.h>

Sphere::Sphere()
{
	this->position = Vector(0.0f, 0.0f, 0.0f);
	this->radius = 1.0f;
}
Sphere::Sphere(Vector position, float radius)
{
	this->position = position;
	this->radius = radius;
}

Sphere::Sphere(const Sphere& orig)
{
	this->position = orig.position;
	this->radius = orig.radius;
}

Sphere::~Sphere()
{
}

void Sphere::draw() const
{
	
}

Vector Sphere::getPosition() const
{
	return position;
}
float Sphere::getRadius() const
{
	return radius;
}

AxisAlignedBox Sphere::getAxisAlignedBox() const
{

}
ObjectOrientedBox Sphere::getObjectOrientedBox() const
{
	
}

Sphere Sphere::transform(Vector position) const
{
	
}

bool Sphere::collision(float x, float y, float z) const
{
	if(x > position[0] - radius && x < position[0] + radius &&
		y > position[1] - radius && y < position[1] + radius &&
		z > position[2] - radius && z < position[2] + radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Sphere::collision(const Vector& position) const
{
	return this->collision(position[0], position[1], position[2]);
}
bool Sphere::collision(const Sphere& sphere) const
{
	for(int i = 0; i < 3; i++)
	{
		if(abs(this->position[i] - sphere.position[i]) > this->radius + sphere.radius)
		{
			return false;
		}
	}

	return true;
}
bool Sphere::collision(const AxisAlignedBox& box) const
{
	return box.collision(*this);
}
bool Sphere::collision(const ObjectOrientedBox& box) const
{
	return box.collision(*this);
}

