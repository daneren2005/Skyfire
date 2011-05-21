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
	ObjectOrientedBox(Array<Vector> points);
	ObjectOrientedBox(const ObjectOrientedBox& orig);
	virtual ~ObjectOrientedBox();

	void draw() const;

	Array<Vector> getPoints() const;

	AxisAlignedBox getAxisAlignedBox() const;
	Sphere getSphere() const;
	ObjectOrientedBox transform(Vector position, Vector angle) const;

	bool collision(float x, float y, float z) const;
	bool collision(const Vector& position) const;
	bool collision(const Sphere& sphere) const;
	bool collision(const AxisAlignedBox& box) const;
	bool collision(const ObjectOrientedBox& box) const;
private:
    Array<Vector> points;
};

#endif	/* _OBJECTORIENTEDBOX_H */

