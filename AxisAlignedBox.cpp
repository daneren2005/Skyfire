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

#include "AxisAlignedBox.h"
#include <GL/gl.h>

#include "Sphere.h"
#include "ObjectOrientedBox.h"
#include "Matrix4.h"
#include <stdlib.h>

AxisAlignedBox::AxisAlignedBox()
{

}
AxisAlignedBox::AxisAlignedBox(float lx, float ly, float lz, float ux, float uy, float uz)
{
	this->min[0] = lx;
	this->min[1] = ly;
	this->min[2] = lz;
	this->max[0] = ux;
	this->max[1] = uy;
	this->max[2] = uz;
}
AxisAlignedBox::AxisAlignedBox(Vector min, Vector max)
{
	this->min = min;
	this->max = max;
}
AxisAlignedBox::AxisAlignedBox(const AxisAlignedBox& orig)
{
	this->min = orig.min;
	this->max = orig.max;
}

AxisAlignedBox::~AxisAlignedBox()
{
}

void AxisAlignedBox::draw() const
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Draw a red box
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
		glVertex3f(this->min[0], this->min[1], this->min[2]);
		glVertex3f(this->min[0], this->min[1], this->max[2]);

		glVertex3f(this->min[0], this->min[1], this->min[2]);
		glVertex3f(this->min[0], this->max[1], this->min[2]);

		glVertex3f(this->min[0], this->min[1], this->min[2]);
		glVertex3f(this->max[0], this->min[1], this->min[2]);

		glVertex3f(this->min[0], this->min[1], this->max[2]);
		glVertex3f(this->min[0], this->max[1], this->max[2]);

		glVertex3f(this->min[0], this->min[1], this->max[2]);
		glVertex3f(this->max[0], this->min[1], this->max[2]);

		glVertex3f(this->min[0], this->max[1], this->min[2]);
		glVertex3f(this->max[0], this->max[1], this->min[2]);

		glVertex3f(this->min[0], this->max[1], this->min[2]);
		glVertex3f(this->min[0], this->max[1], this->max[2]);

		glVertex3f(this->max[0], this->min[1], this->min[2]);
		glVertex3f(this->max[0], this->max[1], this->min[2]);

		glVertex3f(this->max[0], this->min[1], this->min[2]);
		glVertex3f(this->max[0], this->min[1], this->max[2]);

		glVertex3f(this->min[0], this->max[1], this->max[2]);
		glVertex3f(this->max[0], this->max[1], this->max[2]);

		glVertex3f(this->max[0], this->min[1], this->max[2]);
		glVertex3f(this->max[0], this->max[1], this->max[2]);

		glVertex3f(this->max[0], this->max[1], this->min[2]);
		glVertex3f(this->max[0], this->max[1], this->max[2]);
	glEnd();
}

Vector AxisAlignedBox::getMin() const
{
	return min;
}
Vector AxisAlignedBox::getMax() const
{
	return max;
}

Array<Vector> AxisAlignedBox::getPoints() const
{
	Array<Vector> points(8);

	// Create 8 points from possible combinations of points
	points[0] = Vector(this->min[0], this->min[1], this->min[2]);
	points[1] = Vector(this->min[0], this->min[1], this->max[2]);
	points[2] = Vector(this->min[0], this->max[1], this->min[2]);
	points[3] = Vector(this->min[0], this->max[1], this->max[2]);
	points[4] = Vector(this->max[0], this->min[1], this->min[2]);
	points[5] = Vector(this->max[0], this->min[1], this->max[2]);
	points[6] = Vector(this->max[0], this->max[1], this->min[2]);
	points[7] = Vector(this->max[0], this->max[1], this->max[2]);

	return points;
}

ObjectOrientedBox AxisAlignedBox::getObjectOrientedBox() const
{
	return ObjectOrientedBox(this->getPoints());
}
Sphere AxisAlignedBox::getSphere() const
{
	Vector diff = (this->max - this->min) / 2.0f;
	Vector mid = this->min + diff;

	return Sphere(mid, diff.magnitude());
}

AxisAlignedBox AxisAlignedBox::transform(Vector position, Vector angle) const
{
	// Get points that make up the box
	Array<Vector> points = this->getPoints();

	// Translation of all the points
	for(int i = 0; i < points.size(); i++)
	{
		// Rotation
		Matrix4 rotate = Matrix4::rotateObject(angle);
		points[i] = rotate * points[i];

		// Translation
		points[i][0] += position[0];
		points[i][1] += position[1];
		points[i][2] -= position[2];
	}

	// Re axis align the new box
	// Will not give as perfect of a bounding box as rerunning original algorithm on transformed object
	Vector min2(points[0]);
	Vector max2(points[0]);
	for(int i = 1; i < points.size(); i++)
	{
		for(int j = 0; j < 3; j++)
		{
			if(points[i][j] < min2[j])
			{
				min2[j] = points[i][j];
			}
			if(points[i][j] > max2[j])
			{
				max2[j] = points[i][j];
			}
		}
	}

	/*console << "Orig: " << min[0] << " " << min[1] << " " << min[2] << "   " << max[0] << " " << max[1] << " " << max[2] << newline;
	console << "Position: " << position[0] << " " << position[1] << " " << position[2] << newline;
	console << "New: " << min2[0] << " " << min2[1] << " " << min2[2] << "   " << max2[0] << " " << max2[1] << " " << max2[2] << newline;*/

	return AxisAlignedBox(min2, max2);
}

bool AxisAlignedBox::collision(float x, float y, float z) const
{
	if(x > this->min[0] && x < this->max[0] && y > this->min[1] && y < this->max[1] && z > this->min[2] && z < this->max[2])
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool AxisAlignedBox::collision(const Vector& position) const
{
	return this->collision(position[0], position[1], position[2]);
}
bool AxisAlignedBox::collision(const Sphere& sphere) const
{
	Vector width = (this->max - this->min) * 0.5f;
	Vector midPoint = width + this->min;

	for(int i = 0; i < 3; i++)
	{
		if(abs(sphere.getPosition()[i] - midPoint[i]) > sphere.getRadius() + width[i])
		{
			return false;
		}
	}

	return true;
}
bool AxisAlignedBox::collision(const AxisAlignedBox& box) const
{
	for(int i = 0; i < 3; i++)
	{
		if(this->max[i] < box.min[i] || this->min[i] > box.max[i])
		{
			return false;
		}
	}

	return true;
}

bool AxisAlignedBox::collision(const ObjectOrientedBox& box) const
{
    return box.collision(*this);
}

