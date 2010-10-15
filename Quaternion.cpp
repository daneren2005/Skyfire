/* 
 * File:   Quaternion.cpp
 * Author: scott
 * 
 * Created on October 13, 2010, 10:24 AM
 */

#include "Quaternion.h"
#include "const.h"
#include <cmath>

#include <iostream>

Quaternion::Quaternion()
{
	pos[0] = 0.0f;
	pos[1] = 0.0f;
	pos[2] = 0.0f;
	pos[3] = 0.0f;
}

Quaternion::Quaternion(float x, float y, float z)
{
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
	pos[3] = 0.0f;
}

Quaternion::Quaternion(float x, float y, float z, float degrees)
{
	float angle = ((degrees / 180.0f) * PI);
	float result = std::sin(angle  / 2.0f);

	pos[3] = std::cos(angle / 2.0f);
	pos[0] = x * result;
	pos[1] = y * result;
	pos[2] = z * result;
}

Quaternion::Quaternion(const Quaternion& orig)
{
	pos[0] = orig.pos[0];
	pos[1] = orig.pos[1];
	pos[2] = orig.pos[2];
	pos[3] = orig.pos[3];
}

Quaternion::~Quaternion()
{
}

float* Quaternion::getMatrix()
{
	float* matrix = new float[16];

	matrix[0] = 1.0f - 2.0f * (pos[1] * pos[1] + pos[2] * pos[2]);
	matrix[1] = 2.0f * (pos[0] * pos[1] - pos[2] * pos[3]);
	matrix[2] = 2.0f * (pos[0] * pos[2] + pos[1] * pos[3]);
	matrix[3] = 0.0f;

	matrix[4] = 2.0f * (pos[0] * pos[1] + pos[2] * pos[3]);
	matrix[5] = 1.0f - 2.0f * ( pos[0] * pos[0] + pos[2] * pos[2] );
	matrix[6] = 2.0f * ( pos[1] * pos[2] - pos[0] * pos[3] );
	matrix[7] = 0.0f;

	matrix[8] = 2.0f * (pos[0] * pos[2] - pos[1] * pos[3]);
	matrix[9] = 2.0f * (pos[2] * pos[1] + pos[0] * pos[3] );
	matrix[10] = 1.0f - 2.0f * ( pos[0] * pos[0] + pos[1] * pos[1] );
	matrix[11] = 0.0f;

	matrix[12] = 0.0f;
	matrix[13] = 0.0f;
	matrix[14] = 0.0f;
	matrix[15] = 1.0f;

	return matrix;
}

Quaternion Quaternion::operator*(const Quaternion& rhs)
{
	Quaternion r;

	r.pos[3] = pos[3]*rhs.pos[3] - pos[0]*rhs.pos[0] - pos[1]*rhs.pos[1] - pos[2]*rhs.pos[2];
	r.pos[0] = pos[3]*rhs.pos[0] + pos[0]*rhs.pos[3] + pos[1]*rhs.pos[2] - pos[2]*rhs.pos[1];
	r.pos[1] = pos[3]*rhs.pos[1] + pos[1]*rhs.pos[3] + pos[2]*rhs.pos[0] - pos[0]*rhs.pos[2];
	r.pos[2] = pos[3]*rhs.pos[2] + pos[2]*rhs.pos[3] + pos[0]*rhs.pos[1] - pos[1]*rhs.pos[0];

	return(r);
}

Vector Quaternion::operator*(const Vector& rhs)
{
	Quaternion vec(rhs.x(), rhs.y(), rhs.z());
	Quaternion res = vec * !(*this);
	res = *this * res;

	return Vector(res.pos[0], res.pos[1], res.pos[2]);
}

Quaternion Quaternion::operator!()
{
	Quaternion q(-pos[0], -pos[1], -pos[2]);
	q.pos[3] = pos[3];
	return q;
}

void Quaternion::normalize()
{
	float temp = pos[3] * pos[3] + pos[0] * pos[0] + pos[1] * pos[1] + pos[2] * pos[2];
	if(temp!=0.f)
	{
		float mag = sqrt(temp);
		pos[3] /= mag;
		pos[0] /= mag;
		pos[1] /= mag;
		pos[2] /= mag;
	}
}
