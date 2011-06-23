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

#include "ObjectOrientedBox.h"
#include <GL/gl.h>

#include "AxisAlignedBox.h"
#include "Sphere.h"

#include "Matrix4.h"

ObjectOrientedBox::ObjectOrientedBox()
{
	
}
ObjectOrientedBox::ObjectOrientedBox(Array<Vector> points)
{
	this->points = points;
}

ObjectOrientedBox::ObjectOrientedBox(const ObjectOrientedBox& orig)
{
    this->points = orig.points;
}

ObjectOrientedBox::~ObjectOrientedBox()
{
}

void ObjectOrientedBox::draw() const
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Draw a red box
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
		glVertex3f(points[0][0], points[0][1], points[0][2]);
		glVertex3f(points[1][0], points[1][1], points[1][2]);

		glVertex3f(points[0][0], points[0][1], points[0][2]);
		glVertex3f(points[2][0], points[2][1], points[2][2]);

		glVertex3f(points[0][0], points[0][1], points[0][2]);
		glVertex3f(points[4][0], points[4][1], points[4][2]);

		glVertex3f(points[1][0], points[1][1], points[1][2]);
		glVertex3f(points[3][0], points[3][1], points[3][2]);

		glVertex3f(points[1][0], points[1][1], points[1][2]);
		glVertex3f(points[5][0], points[5][1], points[5][2]);

		glVertex3f(points[2][0], points[2][1], points[2][2]);
		glVertex3f(points[6][0], points[6][1], points[6][2]);

		glVertex3f(points[2][0], points[2][1], points[2][2]);
		glVertex3f(points[3][0], points[3][1], points[3][2]);

		glVertex3f(points[4][0], points[4][1], points[4][2]);
		glVertex3f(points[6][0], points[6][1], points[6][2]);

		glVertex3f(points[4][0], points[4][1], points[4][2]);
		glVertex3f(points[5][0], points[5][1], points[5][2]);

		glVertex3f(points[3][0], points[3][1], points[3][2]);
		glVertex3f(points[7][0], points[7][1], points[7][2]);

		glVertex3f(points[5][0], points[5][1], points[5][2]);
		glVertex3f(points[7][0], points[7][1], points[7][2]);

		glVertex3f(points[6][0], points[6][1], points[6][2]);
		glVertex3f(points[7][0], points[7][1], points[7][2]);
	glEnd();
}

Array<Vector> ObjectOrientedBox::getPoints() const
{
	return this->points;
}

AxisAlignedBox ObjectOrientedBox::getAxisAlignedBox() const
{
	Vector minV(points[0]);
	Vector maxV(points[0]);
	for(int i = 1; i < points.size(); i++)
	{
		for(int j = 0; j < 3; j++)
		{
			if(points[i][j] < minV[j])
			{
				minV[j] = points[i][j];
			}
			if(points[i][j] > maxV[j])
			{
				maxV[j] = points[i][j];
			}
		}
	}

	return AxisAlignedBox(minV, maxV);
}

Sphere ObjectOrientedBox::getSphere() const
{
	return getAxisAlignedBox().getSphere();
}

ObjectOrientedBox ObjectOrientedBox::transform(Vector position, Vector angle) const
{
	// Get points that make up the box
	Array<Vector> newPoints = this->getPoints();

	// Translation of all the points
	for(int i = 0; i < newPoints.size(); i++)
	{
		// Rotation
		Matrix4 rotate = Matrix4::rotateObject(angle);
		newPoints[i] = rotate * newPoints[i];

		// Translation
		newPoints[i][0] += position[0];
		newPoints[i][1] += position[1];
		newPoints[i][2] -= position[2];
	}

	return ObjectOrientedBox(newPoints);
}

bool ObjectOrientedBox::collision(float x, float y, float z) const
{
	return false;
}
bool ObjectOrientedBox::collision(const Vector& position) const
{
	return false;
}
bool ObjectOrientedBox::collision(const Sphere& sphere) const
{
	return false;
}
bool ObjectOrientedBox::collision(const AxisAlignedBox& box) const
{
	return false;
}
bool ObjectOrientedBox::collision(const ObjectOrientedBox& box) const
{
	return false;
}

