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

#ifndef _MATRIX4_H
#define	_MATRIX4_H

#include "Matrix.h"
#include "Quaternion.h"
#include "Vector.h"

class Matrix4 : public Matrix
{
public:
	Matrix4();
	Matrix4(float* matrix);
	Matrix4(const Matrix& orig);

	static Matrix identity();

	static Matrix4 modelView(const Vector& location, const Vector& forward, const Vector& up);
	static Matrix4 translate(const Vector& vec);
	static Matrix4 rotateObject(const Vector& vec);
	static Matrix4 rotateMovement(const Vector& vec);
	static Matrix4 scale(const Vector& vec);
};

#endif
