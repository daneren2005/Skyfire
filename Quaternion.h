/* 
 * File:   Quaternion.h
 * Author: scott
 *
 * Created on October 13, 2010, 10:24 AM
 */

#ifndef QUATERNION_H
#define QUATERNION_H

class Quaternion
{
public:
	Quaternion();
	Quaternion(float x, float y, float z, float degrees);
	Quaternion(const Quaternion& orig);
	virtual ~Quaternion();

	float* getMatrix();

	Quaternion operator*(const Quaternion& rhs);
private:
	float pos[4];
};

#endif	/* _QUATERNION_H */

