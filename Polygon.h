/* 
 * File:   Polygon.h
 * Author: scott
 *
 * Created on September 29, 2010, 4:04 PM
 */

#ifndef _POLYGON_H
#define	_POLYGON_H

#include "Triangle.h"
#include "List.h"

class Polygon
{
public:
	Polygon();
	Polygon(const Polygon& orig);
	virtual ~Polygon();

	void addTriangle(Triangle* triangle);
	void draw();
private:
	List<Triangle*> triangles;
	uintptr_t displayList;
};

#endif	/* _POLYGON_H */

