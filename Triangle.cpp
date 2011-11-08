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

#include "Triangle.h"
#include "Matrix.h"

Triangle::Triangle()
{
	
}
Triangle::Triangle(const Vector& a, const Vector& b, const Vector& c)
{
	vertex[0] = a;
	vertex[1] = b;
	vertex[2] = c;
}

Triangle::Triangle(const Triangle& orig)
{
	this->vertex[0] = orig.vertex[0];
	this->vertex[1] = orig.vertex[1];
	this->vertex[2] = orig.vertex[2];
}

Triangle::~Triangle()
{
	
}

float Triangle::getRayIntersection(Vector s, Vector r)
{
	Vector E = vertex[1] - vertex[0];
	Vector F = vertex[2] - vertex[0];
	
	Matrix T(3);
	T(0, 0) = -E[0];
	T(1, 0) = -E[1];
	T(2, 0) = -E[2];
	T(0, 1) = -F[0];
	T(1, 1) = -F[1];
	T(2, 1) = -F[2];
	T(0, 2) = vertex[0][0] - s[0];
	T(1, 2) = vertex[0][1] - s[1];
	T(2, 2) = vertex[0][2] - s[2];
	
	Matrix C(3);
	C(0, 0) = -E[0];
	C(1, 0) = -E[1];
	C(2, 0) = -E[2];
	C(0, 1) = vertex[0][0] - s[0];
	C(1, 1) = vertex[0][1] - s[1];
	C(2, 1) = vertex[0][2] - s[2];
	C(0, 2) = r[0];
	C(1, 2) = r[1];
	C(2, 2) = r[2];
	
	Matrix B(3);
	B(0, 0) = vertex[0][0] - s[0];
	B(1, 0) = vertex[0][1] - s[1];
	B(2, 0) = vertex[0][2] - s[2];
	B(0, 1) = -F[0];
	B(1, 1) = -F[1];
	B(2, 1) = -F[2];
	B(0, 2) = r[0];
	B(1, 2) = r[1];
	B(2, 2) = r[2];
	
	Matrix A(3);
	A(0, 0) = -E[0];
	A(1, 0) = -E[1];
	A(2, 0) = -E[2];
	A(0, 1) = -F[0];
	A(1, 1) = -F[1];
	A(2, 1) = -F[2];
	A(0, 2) = r[0];
	A(1, 2) = r[1];
	A(2, 2) = r[2];
	
	float detT = T.getDet();
	float detA = A.getDet();
	float detB = B.getDet();
	float detC = C.getDet();
	
	float t = detT / detA;
	float beta = detB / detA;
	float ceti = detC / detA;
	
	if(t > 0)
	{
		if(beta > 0 && ceti > 0)
		{
			if(beta + ceti < 1)
			{
				return t;
			}
			else
			{
				return -1.0f;
			}
		}
		else
		{
			return -1.0f;
		}
	}
	else
	{
		return -1.0f;
	}
}

void Triangle::draw()
{
	glVertex3f(this->vertex[0][0], this->vertex[0][1], this->vertex[0][2]);
	glVertex3f(this->vertex[1][0], this->vertex[1][1], this->vertex[1][2]);
	glVertex3f(this->vertex[2][0], this->vertex[2][1], this->vertex[2][2]);
}

