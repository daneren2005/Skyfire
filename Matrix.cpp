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

float* Matrix::getMatrix()
{
	return matrix;
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
