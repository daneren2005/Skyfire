/* 
 * File:   Triangle.h
 * Author: scott
 *
 * Created on September 29, 2010, 4:06 PM
 */

#ifndef _TRIANGLE_H
#define	_TRIANGLE_H

#include "Vector.h"

class Triangle
{
public:
	Triangle();
	Triangle(Vector a, Vector b, Vector c, Vector color);
	Triangle(const Triangle& orig);
	virtual ~Triangle();

	void draw();
private:
	Vector vertex[3];
	Vector color;
};

#endif	/* _TRIANGLE_H */

