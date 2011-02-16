/* 
 * File:   Rectangle3.h
 * Author: scott
 *
 * Created on February 15, 2011, 2:58 PM
 */

#ifndef _RECTANGLE3_H
#define	_RECTANGLE3_H

#include "Vector.h"

class Rectangle3 {
public:
	Rectangle3();
	Rectangle3(float lx, float ly, float lz, float ux, float uy, float uz);
	Rectangle3(const Rectangle3& orig);
	virtual ~Rectangle3();

	void draw();
	bool pointIn(float x, float y, float z);
	bool collision(Rectangle3 rhs);

	float lx, ly, lz, ux, uy, uz;
};

#endif	/* _RECTANGLE3_H */

