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

#include "Matrix.h"

#include <iostream>

Matrix::Matrix(unsigned int dimensions)
{
	this->dim = dimensions;
	this->size = dimensions * dimensions;

	// Create array and set all to 0.0f
	matrix = new float[size];
	for(int i = 0; i < size; i++)
	{
		matrix[i] = 0.0f;
	}
}

Matrix::Matrix(unsigned int dimensions, float* matrix)
{
	this->dim = dimensions;
	this->size = dimensions * dimensions;

	this->matrix = matrix;
}

Matrix::Matrix(const Matrix& orig)
{
	matrix = new float[orig.size];
	for(int i = 0; i < orig.size; i++)
	{
		matrix[i] = orig.matrix[i];
	}
	this->size = orig.size;
	this->dim = orig.dim;
}

Matrix::~Matrix()
{
	delete this->matrix;
}

float* Matrix::operator[](unsigned col)
{
	// return pointer starting at the given row
	return matrix + (dim * col);
}
const float* Matrix::operator[](unsigned col) const
{
	// return pointer starting at the given row
	return matrix + (dim * col);
}

Matrix& Matrix::operator=(const Matrix& orig)
{
	delete matrix;
	
	matrix = new float[orig.size];
	for(int i = 0; i < orig.size; i++)
	{
		matrix[i] = orig.matrix[i];
	}
	this->size = orig.size;
	this->dim = orig.dim; 
}

Matrix Matrix::operator*(const Matrix& rhs)
{
	Matrix result(this->dim);

	// Column of new matrix
	for(int i = 0; i < this->dim; i++)
	{
		// Row of new matrix
		for(int j = 0; j < dim; j++)
		{
			result.matrix[i * dim + j] = 0.0f;
			for(int k = 0; k < dim; k++)
			{
				result.matrix[i * dim + j] += this->matrix[i * dim + k] * rhs.matrix[k * dim + j];
			}
		}
	}

	return result;
}

Vector Matrix::operator*(const Vector& rhs)
{
	Vector result;

	for(int i = 0; i < 3; i++)
	{
		result[i] += matrix[i] * rhs.x();
		result[i] += matrix[dim + i] * rhs.y();
		result[i] += matrix[dim * 2 + i] * rhs.z();
	}

	return result;
}

float& Matrix::operator()(uint col, uint row)
{
	return matrix[row * dim + col];
}
const float& Matrix::operator()(uint col, uint row) const
{
	return matrix[row * dim + col];
}

float* Matrix::getMatrix()
{
	return matrix;
}

float Matrix::getDet() const
{
	// TODO: Needs to be generic (this is for 3x3 only)!
	return (*this)(0, 0) * (*this)(1, 1) * (*this)(2, 2) + (*this)(0, 1) * (*this)(1, 2) * (*this)(2, 0) +
		(*this)(0, 2) * (*this)(1, 0) * (*this)(2, 1) - (*this)(2, 0) * (*this)(1, 1) * (*this)(0, 2) -
		(*this)(2, 1) * (*this)(1, 2) * (*this)(0, 0) - (*this)(2, 2) * (*this)(1, 0) * (*this)(0, 1);
}

Matrix Matrix::identity(unsigned int dimensions)
{
	Matrix m(dimensions);
	for(int i = 0; i < m.size; i += dimensions + 1)
	{
		m.matrix[i] = 1.0f;
	}
	return m;
}
