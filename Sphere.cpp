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

#include "Sphere.h"
#include "AxisAlignedBox.h"
#include "ObjectOrientedBox.h"

#include <stdlib.h>
#include <GL/glu.h>

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
	GLUquadricObj *quadratic = gluNewQuadric();
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	gluQuadricNormals(quadratic, GLU_SMOOTH);

	glPushMatrix();
	glTranslatef(position[0], position[1], position[2]);
	gluSphere(quadratic, radius, 32, 32);
	glPopMatrix();

	gluDeleteQuadric(quadratic);
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
	Vector min, max;

	for(int i = 0; i < 3; i++)
	{
		min[i] = position[i] - radius;
		max[i] = position[i] + radius;
	}

	return AxisAlignedBox(min, max);
}
ObjectOrientedBox Sphere::getObjectOrientedBox() const
{
	Vector min, max;

	for(int i = 0; i < 3; i++)
	{
		min[i] = position[i] - radius;
		max[i] = position[i] + radius;
	}

	Array<Vector> points(8);
	// Create 8 points from possible combinations of points
	points[0] = Vector(min[0], min[1], min[2]);
	points[1] = Vector(min[0], min[1], max[2]);
	points[2] = Vector(min[0], max[1], min[2]);
	points[3] = Vector(min[0], max[1], max[2]);
	points[4] = Vector(max[0], min[1], min[2]);
	points[5] = Vector(max[0], min[1], max[2]);
	points[6] = Vector(max[0], max[1], min[2]);
	points[7] = Vector(max[0], max[1], max[2]);

	return ObjectOrientedBox(points);
}

Sphere Sphere::transform(Vector position) const
{
	position[0] = this->position[0] + position[0];
	position[1] = this->position[1] + position[1];
	position[2] = this->position[2] - position[2];

	return Sphere(position, this->radius);
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

