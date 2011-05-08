#ifndef _MODEL_H
#define	_MODEL_H

#include "Mesh.h"
#include "AxisAlignedBox.h"

class Model : public Array<Mesh*>
{
public:
	Model();
	Model(unsigned long size);
	Model(const Model& orig);
	virtual ~Model();

	AxisAlignedBox getBoundingBox();
	void computeBoundingBox();

	long numTriangles();

	void draw();
private:
	AxisAlignedBox boundingBox;
};

#endif
