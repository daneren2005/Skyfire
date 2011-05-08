/* 
 * File:   AxisAlignedBox.h
 * Author: scott
 *
 * Created on February 15, 2011, 2:58 PM
 */

#ifndef _AxisAlignedBox_H
#define	_AxisAlignedBox_H

#include "Vector.h"

class Sphere;
class ObjectOrientedBox;

class AxisAlignedBox
{
public:
	AxisAlignedBox();
	AxisAlignedBox(float lx, float ly, float lz, float ux, float uy, float uz);
	AxisAlignedBox(Vector min, Vector max);
	AxisAlignedBox(const AxisAlignedBox& orig);
	virtual ~AxisAlignedBox();

	void draw() const;

	Vector getMin() const;
	Vector getMax() const;
	Array<Vector> getPoints() const;
	AxisAlignedBox transformBox(Vector position, Vector angle) const;

	bool collision(float x, float y, float z) const;
	bool collision(const Vector& position) const;
	bool collision(const Sphere& sphere) const;
	bool collision(const AxisAlignedBox& box) const;
	bool collision(const ObjectOrientedBox& box) const;
private:
	Vector min, max;
};

#endif	/* _AxisAlignedBox_H */

