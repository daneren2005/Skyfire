#include "Matrix4.h"

#include <iostream>

Matrix4::Matrix4() : Matrix(4)
{ }

Matrix4::Matrix4(const Matrix& orig) : Matrix(orig)
{ }

float* Matrix4::operator[](unsigned col)
{
	// return pointer starting at the given row
	return matrix + (dim * col);
}

float* Matrix4::getMatrix()
{
	return matrix;
}

Matrix Matrix4::identity()
{
	return Matrix::identity(4);
}

Matrix4 Matrix4::translate(const Vector& vec)
{
	Matrix4 m = Matrix4::identity();
	m.matrix[12] = vec.x();
	m.matrix[13] = vec.y();
	m.matrix[14] = vec.z();

	/*for(int i = 0; i < m.size; i++)
	{
		std::cout << m.matrix[i] << std::endl;
	}
	std::cout << std::endl;*/

	return m;
}

Matrix4 Matrix4::rotate(const Vector& vec)
{

}

Matrix4 Matrix4::scale(const Vector& vec)
{

}
