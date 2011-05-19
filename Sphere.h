/* 
 * File:   Sphere.h
 * Author: scott
 *
 * Created on May 8, 2011, 12:56 AM
 */

#ifndef _SPHERE_H
#define	_SPHERE_H

#include "Vector.h"

class AxisAlignedBox;
class ObjectOrientedBox;

class Sphere
{
public:
	Sphere();
	Sphere(Vector position, float radius);
	Sphere(const Sphere& orig);
	virtual ~Sphere();

	void draw() const;

	Vector getPosition() const;
	float getRadius() const;

	AxisAlignedBox getAxisAlignedBox() const;
	ObjectOrientedBox getObjectOrientedBox() const;
	Sphere transform(Vector position) const;

	bool collision(float x, float y, float z) const;
	bool collision(const Vector& position) const;
	bool collision(const Sphere& sphere) const;
	bool collision(const AxisAlignedBox& box) const;
	bool collision(const ObjectOrientedBox& box) const;
private:
	Vector position;
	float radius;
};

#endif	/* _SPHERE_H */

