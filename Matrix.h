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

#ifndef _MATRIX_H
#define	_MATRIX_H

#include "Vector.h"

class Matrix
{
public:
	Matrix(unsigned int dimensions);
	Matrix(unsigned int dimensions, float* matrix);
	Matrix(const Matrix& orig);
	~Matrix();

	float* operator[](unsigned col);
	const float* operator[](unsigned col) const;
	Matrix operator*(const Matrix& rhs);
	Vector operator*(const Vector& rhs);
	
	float& operator()(uint col, uint row);
	const float& operator()(uint col, uint row) const;

	virtual float* getMatrix();
	
	float getDet() const;

	static Matrix identity(unsigned int dimensions);
protected:
	int size;
	int dim;
	float* matrix;
};

#endif
