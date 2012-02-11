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

#include "Matrix4.h"

#include <iostream>

Matrix4::Matrix4() : Matrix(4)
{ }

Matrix4::Matrix4(float* matrix) : Matrix(4, matrix)
{ }

Matrix4::Matrix4(const Matrix& orig) : Matrix(orig)
{ }
Matrix4::~Matrix4()
{
	delete this->matrix;
}

Matrix Matrix4::identity()
{
	return Matrix::identity(4);
}

Matrix4 Matrix4::modelView(const Vector& location, const Vector& forward, const Vector& up)
{
	Vector x = up * forward;

	Matrix4 m = Matrix4::identity();
	if(x[0] != 0.0f)
		m[0][0] = x[0];
	m[0][1] = x[1];
	m[0][2] = x[2];
	m[0][3] = 0.0f;

	m[1][0] = up[0];
	if(up[1] != 0.0f)
		m[1][1] = up[1];
	m[1][2] = up[2];
	m[1][3] = 0.0f;

	m[2][0] = forward[0];
	m[2][1] = forward[1];
	if(forward[2] != 0.0f)
		m[2][2] = forward[2];
	m[2][3] = 0.0f;

	m[3][0] = location[0];
	m[3][1] = location[1];
	m[3][2] = location[2];
	m[3][3] = 1.0f;

	return m;
}

Matrix4 Matrix4::translate(const Vector& vec)
{
	Matrix4 m = Matrix4::identity();
	m.matrix[12] = vec.x();
	m.matrix[13] = vec.y();
	m.matrix[14] = vec.z();

	return m;
}

Matrix4 Matrix4::rotateObject(const Vector& vec)
{
	Quaternion x(1.0f, 0.0f, 0.0f, vec.x());
	Quaternion y(0.0f, 1.0f, 0.0f, vec.y());
	Quaternion z(0.0f, 0.0f, 1.0f, vec.z());
	Quaternion rotation = z * y * x;

	Matrix4 matrix(rotation.getMatrix());
	return matrix;
}
Matrix4 Matrix4::rotateMovement(const Vector& vec)
{
	Quaternion x(1.0f, 0.0f, 0.0f, vec.x());
	Quaternion y(0.0f, 1.0f, 0.0f, vec.y());
	Quaternion z(0.0f, 0.0f, 1.0f, vec.z());
	Quaternion rotation = z * x * y;

	Matrix4 matrix(rotation.getMatrix());
	return matrix;
}

Matrix4 Matrix4::scale(const Vector& vec)
{
	Matrix4 m = Matrix4::identity();
	m.matrix[0] = vec.x();
	m.matrix[5] = vec.y();
	m.matrix[10] = vec.z();
	return m;
}
