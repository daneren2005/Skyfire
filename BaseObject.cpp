/*
 * File:   BaseObject.cpp
 * Author: scott
 *
 * Created on July 13, 2010, 8:20 PM
 */

#include "BaseObject.h"

// #include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include "const.h"
#include <cmath>

// #include <iostream>

BaseObject::BaseObject()
{
	position = Vector(0.0f, 0.0f, 0.0f);
	angle = Vector(0.0f, 0.0f, 0.0f);
	this->shape = NULL;
}
BaseObject::BaseObject(float x, float y, float z)
{
	position = Vector(x, y, z);
	this->shape = NULL;
}

BaseObject::BaseObject(const BaseObject& orig)
{
}

BaseObject::~BaseObject()
{
}

void BaseObject::moveByAbsolute(float x, float y, float z)
{
	Vector amount(x, y, z);
	this->position = this->position + amount;
}
void BaseObject::moveByAbsolute(const Vector& amount)
{
	this->position = this->position + amount;
}
void BaseObject::moveByReference(float x, float y, float z)
{
	// TODO: reference
	Vector amount(x, y, z);
	this->position = this->position + amount;
}
void BaseObject::moveByReference(const Vector& amount)
{
	// TODO: reference
	this->position = this->position + amount;
}
void BaseObject::moveTo(float x, float y, float z)
{
	this->position = Vector(x, y, z);
}
void BaseObject::moveTo(const Vector& amount)
{
	this->position = amount;
}
void BaseObject::rotateByAbsolute(float x, float y, float z)
{
	this->rotateByAbsolute(Vector(y, x, z));
}
void BaseObject::rotateByAbsolute(const Vector& amount)
{
	this->angle = this->angle + amount;
	this->angle = this->angle % 360;

}
void BaseObject::rotateByReference(float x, float y, float z)
{
	// TODO: reference
	this->angle = this->angle + Vector(y, x, z);
}
void BaseObject::rotateByReference(const Vector& amount)
{
	// TODO: reference
	this->angle = this->angle + amount;
}

void BaseObject::draw(Vector cameraPosition, Vector cameraAngle)
{
	glLoadIdentity();

	float x = (cameraAngle[1] * PI) / 180;
	float y = (cameraAngle[0] * PI) / 180;
	float z = (cameraAngle[2] * PI) / 180;

	Vector oldPosition = position - cameraPosition;
	Vector newPosition;
	newPosition[0] = oldPosition[2] * std::sin(x) + oldPosition[0] * std::cos(x)	// x rotation (actual y)
		- oldPosition[1] * std::sin(z);												// z rotation
	newPosition[1] = oldPosition[1] * std::cos(y) - oldPosition[2] * std::sin(y)	// y rotation (actual x)
		+ oldPosition[0] * std::sin(z);												// z rotation
	newPosition[2] = oldPosition[2] * std::cos(x) - oldPosition[0] * std::sin(x)	// x rotation (actual y)
		+ oldPosition[1] * std::sin(y);												// y rotation (actual x)
	glTranslatev(newPosition);

	glRotatev(angle);

	if(!glIsList(this->displayList))
	{
        #ifdef WIN32
            MessageBox(NULL, TEXT("No list"), NULL, NULL);
        #endif
	}
	// glCallList(this->displayList);

	if(this->shape != NULL)
	{
		this->shape->draw();
	}

	/*glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);

		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();*/
}

void BaseObject::load()
{

}
