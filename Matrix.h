/*
 * File:   Matrix.h
 * Author: scott
 *
 * Created on July 13, 2010, 8:22 PM
 */

#ifndef _MATRIX_H
#define	_MATRIX_H

class Matrix
{
public:
	Matrix(unsigned int dimensions);
	Matrix(unsigned int dimensions, float* matrix);
	Matrix(const Matrix& orig);
	~Matrix();

	float* operator[](unsigned col);
	Matrix operator*(const Matrix& rhs);

	virtual float* getMatrix();

	static Matrix identity(unsigned int dimensions);
protected:
	int size;
	int dim;
	float* matrix;
};

#endif
