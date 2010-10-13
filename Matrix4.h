/*
 * File:   Matrix4.h
 * Author: scott
 *
 * Created on July 13, 2010, 8:22 PM
 */

#ifndef _MATRIX4_H
#define	_MATRIX4_H

#include "Matrix.h"
#include "Vector.h"

class Matrix4 : Matrix
{
public:
	Matrix4();
	Matrix4(const Matrix& orig);

	float* operator[](unsigned col);
	float* getMatrix();

	static Matrix identity();

	static Matrix4 translate(const Vector& vec);
	static Matrix4 rotate(const Vector& vec);
	static Matrix4 scale(const Vector& vec);
};

#endif
