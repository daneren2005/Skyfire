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

#ifndef _AxisAlignedBox_H
#define	_AxisAlignedBox_H

#include "Vector.h"

class Sphere;
class ObjectOrientedBox;

class AxisAlignedBox
{
public:
	AxisAlignedBox();
	AxisAlignedBox(float lx, float ly, float lz, float ux, float uy, float uz);
	AxisAlignedBox(Vector min, Vector max);
	AxisAlignedBox(const AxisAlignedBox& orig);
	virtual ~AxisAlignedBox();

	void draw() const;

	Vector getMin() const;
	Vector getMax() const;
	Array<Vector> getPoints() const;

	ObjectOrientedBox getObjectOrientedBox() const;
	Sphere getSphere() const;
	AxisAlignedBox transform(Vector position, Vector angle) const;

	bool collision(float x, float y, float z) const;
	bool collision(const Vector& position) const;
	bool collision(const Sphere& sphere) const;
	bool collision(const AxisAlignedBox& box) const;
	bool collision(const ObjectOrientedBox& box) const;
private:
	Vector min, max;
};

#endif	/* _AxisAlignedBox_H */

