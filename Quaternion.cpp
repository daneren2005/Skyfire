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
	float xAngle = (x / 180.0f) * PI;
	float yAngle = (y / 180.0f) * PI;
	float zAngle = (z / 180.0f) * PI;

	pos[0] = std::sin(yAngle) * std::cos(xAngle) * std::cos(zAngle) - std::cos(yAngle) * std::sin(xAngle) * std::sin(zAngle);
	pos[1] = std::cos(yAngle) * std::sin(xAngle) * std::cos(zAngle) + std::sin(yAngle) * std::cos(xAngle) * std::sin(zAngle);
	pos[2] = std::cos(yAngle) * std::cos(xAngle) * std::sin(zAngle) - std::sin(yAngle) * std::sin(xAngle) * std::cos(zAngle);
	pos[3] = std::cos(yAngle) * std::cos(xAngle) * std::cos(zAngle) + std::sin(yAngle) * std::sin(xAngle) * std::sin(zAngle);

	this->normalize();
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

Vector Quaternion::getAxis()
{
	float scale = std::sqrt(pos[0] * pos[0] + pos[1] * pos[1] + pos[2] * pos[2]);
	return Vector(pos[0] / scale, pos[1] / scale, pos[2] / scale);
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
	// TODO: Should be vector...
	Quaternion vec(rhs[0], rhs[1], rhs[2]);
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
