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
