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

#ifndef _SPHERE_H
#define	_SPHERE_H

#include "Vector.h"

class AxisAlignedBox;
class ObjectOrientedBox;

class Sphere
{
public:
	Sphere();
	Sphere(Vector position, float radius);
	Sphere(const Sphere& orig);
	virtual ~Sphere();

	void draw() const;

	Vector getPosition() const;
	float getRadius() const;

	AxisAlignedBox getAxisAlignedBox() const;
	ObjectOrientedBox getObjectOrientedBox() const;
	Sphere transform(Vector position) const;

	bool collision(float x, float y, float z) const;
	bool collision(const Vector& position) const;
	bool collision(const Sphere& sphere) const;
	bool collision(const AxisAlignedBox& box) const;
	bool collision(const ObjectOrientedBox& box) const;
private:
	Vector position;
	float radius;
};

#endif	/* _SPHERE_H */

