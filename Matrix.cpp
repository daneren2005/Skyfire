#include "Matrix.h"

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

}

Matrix::~Matrix()
{

}

float* Matrix::operator[](unsigned row)
{
	// return pointer starting at the given row
	return matrix + (dim * row);
}

float* Matrix::getMatrix()
{
	return matrix;
}
