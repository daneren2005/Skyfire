/*
 * File:   Matrix4.h
 * Author: scott
 *
 * Created on July 13, 2010, 8:22 PM
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

	static Matrix4 translate(const Vector& vec);
	static Matrix4 rotateObject(const Vector& vec);
	static Matrix4 rotateMovement(const Vector& vec);
	static Matrix4 scale(const Vector& vec);
};

#endif
