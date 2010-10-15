/* 
 * File:   Quaternion.h
 * Author: scott
 *
 * Created on October 13, 2010, 10:24 AM
 */

#ifndef QUATERNION_H
#define QUATERNION_H

#include "Vector.h"

class Quaternion
{
public:
	Quaternion();
	Quaternion(float x, float y, float z);
	Quaternion(float x, float y, float z, float degrees);
	Quaternion(const Quaternion& orig);
	virtual ~Quaternion();

	float* getMatrix();

	Quaternion operator*(const Quaternion& rhs);
	Vector operator*(const Vector& rhs);

	Quaternion operator!();
private:
	float pos[4];

	void normalize();
};

#endif	/* _QUATERNION_H */

