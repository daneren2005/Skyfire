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

#ifndef QUATERNION_H
#define QUATERNION_H

#include "Vector.h"

class Quaternion
{
public:
	Quaternion();
	Quaternion(float x, float y, float z);
	Quaternion(float x, float y, float z, float degrees);
	Quaternion(const Quaternion& orig);
	virtual ~Quaternion();

	float* getMatrix();
	Vector getAxis();

	Quaternion operator*(const Quaternion& rhs);
	Vector operator*(const Vector& rhs);

	Quaternion operator!();
private:
	float pos[4];

	void normalize();
};

#endif	/* _QUATERNION_H */

