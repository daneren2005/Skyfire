/*
 * File:   Mesh.h
 * Author: scott
 *
 * Created on September 29, 2010, 4:04 PM
 */

#ifndef _Mesh_H
#define	_Mesh_H

#include "Array.h"
#include "Triangle.h"

struct Vertex
{
	float position[3];
	float normal[3];
	float color[3];
	float texture[2];
};

class Mesh : public Array<Vertex>
{
public:
	Mesh();
	Mesh(unsigned long size, bool wireFrame = false);
	Mesh(const Mesh& orig);
	virtual ~Mesh();

	void draw();
private:
	bool wireFrame;
};

#endif	/* _Mesh_H */

