/* 
 * File:   Rectangle3.cpp
 * Author: scott
 * 
 * Created on February 15, 2011, 2:58 PM
 */

#include "Rectangle3.h"
#include <GL/gl.h>

Rectangle3::Rectangle3()
{

}
Rectangle3::Rectangle3(float lx, float ly, float lz, float ux, float uy, float uz)
{
	this->min[0] = lx;
	this->min[1] = ly;
	this->min[2] = lz;
	this->max[0] = ux;
	this->max[1] = uy;
	this->max[2] = uz;
}
Rectangle3::Rectangle3(Vector min, Vector max)
{
	this->min = min;
	this->max = max;
}
Rectangle3::Rectangle3(const Rectangle3& orig)
{
	this->min = orig.min;
	this->max = orig.max;
}

Rectangle3::~Rectangle3()
{
}

void Rectangle3::draw()
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

Array<Vector> Rectangle3::getPoints()
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

Rectangle3 Rectangle3::transformBox(Vector position, Vector angle)
{
	// Get points that make up the box
	Array<Vector> points = this->getPoints();

	// TODO: rotations on all points
	// Translation
	for(int i = 0; i < points.size(); i++)
	{
		points[i][0] += position[0];
		points[i][1] += position[1];
		points[i][2] += position[2];
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

	return Rectangle3(min2, max2);
}

bool Rectangle3::pointCollision(float x, float y, float z)
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
bool Rectangle3::pointCollision(Vector position)
{
	return this->pointCollision(position[0], position[1], position[2]);
}
bool Rectangle3::rectangleCollision(Rectangle3 box)
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

