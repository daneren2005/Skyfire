#ifndef _MESH_H
#define	_MESH_H

#include "MeshPart.h"
#include "AxisAlignedBox.h"

class Mesh : public Array<MeshPart*>
{
public:
	Mesh();
	Mesh(unsigned long size);
	Mesh(const Mesh& orig);
	virtual ~Mesh();

	AxisAlignedBox getBoundingBox();
	void computeBoundingBox();

	long numTriangles();

	void draw();
private:
	AxisAlignedBox boundingBox;
};

#endif
