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

#include "Ray.h"
#include "Matrix.h"
#include <math.h>

Ray::Ray(const Vector& start, const Vector& end)
{
	this->start = start;
	this->end = end;
}

Ray::Ray(const Ray& orig)
{
	start = orig.start;
	end = orig.end;
}

Ray::~Ray()
{
}

float Ray::getIntersection(const Vector& v1, const Vector& v2, const Vector& v3) const
{	
	Vector E = v2 - v1;
	Vector F = v3 - v1;
	
	Matrix T(3);
	T(0, 0) = -E[0];
	T(1, 0) = -E[1];
	T(2, 0) = -E[2];
	T(0, 1) = -F[0];
	T(1, 1) = -F[1];
	T(2, 1) = -F[2];
	T(0, 2) = v1[0] - start[0];
	T(1, 2) = v1[1] - start[1];
	T(2, 2) = v1[2] - start[2];
	
	Matrix C(3);
	C(0, 0) = -E[0];
	C(1, 0) = -E[1];
	C(2, 0) = -E[2];
	C(0, 1) = v1[0] - start[0];
	C(1, 1) = v1[1] - start[1];
	C(2, 1) = v1[2] - start[2];
	C(0, 2) = end[0];
	C(1, 2) = end[1];
	C(2, 2) = end[2];
	
	Matrix B(3);
	B(0, 0) = v1[0] - start[0];
	B(1, 0) = v1[1] - start[1];
	B(2, 0) = v1[2] - start[2];
	B(0, 1) = -F[0];
	B(1, 1) = -F[1];
	B(2, 1) = -F[2];
	B(0, 2) = end[0];
	B(1, 2) = end[1];
	B(2, 2) = end[2];
	
	Matrix A(3);
	A(0, 0) = -E[0];
	A(1, 0) = -E[1];
	A(2, 0) = -E[2];
	A(0, 1) = -F[0];
	A(1, 1) = -F[1];
	A(2, 1) = -F[2];
	A(0, 2) = end[0];
	A(1, 2) = end[1];
	A(2, 2) = end[2];
	
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

Console& operator<<(Console& c, const Ray& ray)
{
	c << "Start: " << ray.start.x() << "," << ray.start.y() << "," << ray.start.z() 
			<< "; End: " << ray.end.x() << "," << ray.end.y() << "," << ray.end.z();
	return c;
}

