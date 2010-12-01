/*
 * File:   Mesh.h
 * Author: scott
 *
 * Created on September 29, 2010, 4:04 PM
 */

#ifndef _Mesh_H
#define	_Mesh_H

#include "Triangle.h"
#include "Array.h"
#include "List.h"

class Mesh : public Array<Triangle>
{
public:
	Mesh();
	Mesh(unsigned long size, bool wireFrame = false);
	Mesh(const Mesh& orig);
	virtual ~Mesh();

	void draw();
private:
	bool wireFrame;
	int displayList;
};

#endif	/* _Mesh_H */

