#ifndef _MODEL_H
#define	_MODEL_H

#include "Mesh.h"
#include "Rectangle3.h"

class Model : public Array<Mesh*>
{
public:
	Model();
	Model(unsigned long size);
	Model(const Model& orig);
	virtual ~Model();

	Rectangle3 getBoundingBox();
	void setBoundingBox(Rectangle3 boundingBox);


	void draw();
private:
	Rectangle3 boundingBox;
};

#endif
