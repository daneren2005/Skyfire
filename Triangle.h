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

#ifndef _TRIANGLE_H
#define	_TRIANGLE_H

#include "Vector.h"

class Triangle
{
public:
	Triangle();
	Triangle(const Vector& a, const Vector& b, const Vector& c);
	Triangle(const Triangle& orig);
	virtual ~Triangle();
	
	float getRayIntersection(Vector s, Vector r);

	void draw();
private:
	Vector vertex[3];
};

#endif	/* _TRIANGLE_H */

