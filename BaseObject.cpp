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
	
	/*Quaternion x(1.0f, 0.0f, 0.0f, angle.x());
	Quaternion y(0.0f, 1.0f, 0.0f, angle.y());
	Quaternion z(0.0f, 0.0f, 1.0f, angle.z());
	Quaternion rotation = y * x * z;
	Vector move = rotation * amount;*/

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
	this->rotateBy(amount.y(), amount.x(), amount.z());
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

	if(this->shape != NULL)
	{
		this->shape->draw();
	}

	// Get rid of just edited matrix and replace with the fresh camera one
	glPopMatrix();
}

void BaseObject::load()
{

}
