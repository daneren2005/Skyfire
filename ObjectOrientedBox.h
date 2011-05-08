/* 
 * File:   ObjectOrientedBox.h
 * Author: scott
 *
 * Created on May 8, 2011, 1:02 AM
 */

#ifndef _OBJECTORIENTEDBOX_H
#define	_OBJECTORIENTEDBOX_H

#include "Vector.h"

class Sphere;
class AxisAlignedBox;
class ObjectOrientedBox;

class ObjectOrientedBox
{
public:
	ObjectOrientedBox();
	ObjectOrientedBox(const ObjectOrientedBox& orig);
	virtual ~ObjectOrientedBox();

	bool collision(float x, float y, float z) const;
	bool collision(const Vector& position) const;
	bool collision(const Sphere& sphere) const;
	bool collision(const AxisAlignedBox& box) const;
	bool collision(const ObjectOrientedBox& box) const;
private:

};

#endif	/* _OBJECTORIENTEDBOX_H */

