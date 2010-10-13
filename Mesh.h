/*
 * File:   Mesh.h
 * Author: scott
 *
 * Created on September 29, 2010, 4:04 PM
 */

#ifndef _Mesh_H
#define	_Mesh_H

#include "Triangle.h"
#include "List.h"

class Mesh
{
public:
	Mesh();
	Mesh(const Mesh& orig);
	virtual ~Mesh();

	void addTriangle(Triangle* triangle);
	void draw();
private:
	List<Triangle*> triangles;
	int displayList;
};

#endif	/* _Mesh_H */

