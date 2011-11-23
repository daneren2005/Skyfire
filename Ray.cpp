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
	Vector u, v, n;
	u = v2 - v1;
	v = v3 - v1;
	n = u * v;
	
	if(n == Vector())
		return -1.0f;
	
	Vector dir = end - start;
	Vector w1 = start - v1;
	
	float a = -n.dot(w1);
	float b = n.dot(dir);
	if(fabs(b) < 0.00000001)
		return -1.0f;
	
	float r = a / b;
	if(r < 0.0f)
		return -1.0f;
	
	Vector end = dir * r;
	Vector intersect = start + end;
	
	float uu = u.dot(u);
	float uv = u.dot(v);
	float vv = v.dot(v);
	
	Vector w2 = intersect + end;
	float wu = w2.dot(u);
	float wv = w2.dot(v);
	float D = uv * uv - uu * vv;
	
	float s, t;
	s = (uv * wv - vv * wu) / D;
	if (s < 0.0 || s > 1.0)
        return -1.0f;
    t = (uv * wu - uu * wv) / D;
    if (t < 0.0 || (s + t) > 1.0)
        return -1.0f;

    return end.magnitude();
}

Console& operator<<(Console& c, const Ray& ray)
{
	c << "Start: " << ray.start.x() << "," << ray.start.y() << "," << ray.start.z() 
			<< "; End: " << ray.end.x() << "," << ray.end.y() << "," << ray.end.z();
	return c;
}

