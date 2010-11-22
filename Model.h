#ifndef _MODEL_H
#define	_MODEL_H

#include "Mesh.h"

class Model : public Array<Mesh>
{
public:
	Model();
	Model(unsigned long size);
	Model(const Model& orig);
	virtual ~Model();

	void draw();
private:

};

#endif
