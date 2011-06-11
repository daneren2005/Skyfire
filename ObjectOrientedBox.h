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

#ifndef _OBJECTORIENTEDBOX_H
#define	_OBJECTORIENTEDBOX_H

#include "Vector.h"

class Sphere;
class AxisAlignedBox;
class ObjectOrientedBox;

class ObjectOrientedBox
{
public:
	ObjectOrientedBox();
	ObjectOrientedBox(Array<Vector> points);
	ObjectOrientedBox(const ObjectOrientedBox& orig);
	virtual ~ObjectOrientedBox();

	void draw() const;

	Array<Vector> getPoints() const;

	AxisAlignedBox getAxisAlignedBox() const;
	Sphere getSphere() const;
	ObjectOrientedBox transform(Vector position, Vector angle) const;

	bool collision(float x, float y, float z) const;
	bool collision(const Vector& position) const;
	bool collision(const Sphere& sphere) const;
	bool collision(const AxisAlignedBox& box) const;
	bool collision(const ObjectOrientedBox& box) const;
private:
    Array<Vector> points;
};

#endif	/* _OBJECTORIENTEDBOX_H */

