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

#include <iostream>

BaseObject::BaseObject()
{
	position = Vector(0.0f, 0.0f, 0.0f);
	angle = Vector(0.0f, 0.0f, 0.0f);
}
BaseObject::BaseObject(float x, float y, float z)
{
	position = Vector(x, y, z);
}

BaseObject::BaseObject(const BaseObject& orig)
{
}

BaseObject::~BaseObject()
{
}

void BaseObject::moveBy(float x, float y, float z)
{
	Vector amount(x, y, z);
	this->moveBy(amount);
}
void BaseObject::moveBy(const Vector& amount)
{
	this->position = this->position + amount;
}
void BaseObject::moveByDirection(float x, float y, float z)
{
	Vector amount(x, y, z);
	this->moveByDirection(amount);
}
void BaseObject::moveByDirection(const Vector& amount)
{
	Matrix4 rotate = Matrix4::rotateMovement(this->angle);
	Vector move = rotate * amount;

	this->position = this->position + move;
}
void BaseObject::moveTo(float x, float y, float z)
{
	this->position = Vector(x, y, z);
}
void BaseObject::moveTo(const Vector& amount)
{
	this->position = amount;
}
void BaseObject::rotateBy(float x, float y, float z)
{
	Vector vec(y, x, z);
	this->angle = this->angle + vec;
	this->angle = this->angle % 360;
}
void BaseObject::rotateBy(const Vector& amount)
{
	this->rotateBy(amount[1], amount[0], amount[2]);
}

void BaseObject::draw()
{
	glPushMatrix();
	Matrix4 rotate = Matrix4::rotateObject(this->angle);
	Matrix4 translate = Matrix4::translate(this->position);
	Matrix4 transform = rotate * translate;
	glMultMatrixf(transform.getMatrix());

	/*float* f = new float[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, f);
	for(int i = 0; i < 4; i++)
	{
		std::cout << f[i] << " " << f[i + 4] << " " << f[i + 8] << " " << f[i + 12] << std::endl;
	}
	std::cout << std::endl;*/

	this->mesh.draw();

	// Get rid of just edited matrix and replace with the fresh camera one
	glPopMatrix();
}

void BaseObject::load()
{

}
