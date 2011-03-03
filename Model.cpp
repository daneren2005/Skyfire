#include "Model.h"
#include "const.h"

Model::Model() : Array<Mesh*>()
{
	
}

Model::Model(unsigned long size) : Array<Mesh*>(size)
{
	
}

Model::Model(const Model& orig) : Array<Mesh*>(orig)
{
	
}

Model::~Model()
{
	
}

void Model::draw()
{
	glDisable(GL_BLEND);

	// Draw bounding box outline
	this->boundingBox.draw();

	for(int i = 0; i < this->used; i++)
	{
		array[i]->draw();
	}
}

Rectangle3 Model::getBoundingBox()
{
	return this->boundingBox;
}
void Model::computeBoundingBox()
{
	Vector min(MAXFLOAT, MAXFLOAT, MAXFLOAT);
	Vector max(MINFLOAT, MINFLOAT, MINFLOAT);
	for(int i = 0; i < this->used; i++)
	{
		Mesh* mesh = array[i];
		for(int j = 0; j < mesh->size(); j++)
		{
			Vector v = (*mesh)[j].position;
			if(v.x() < min.x())
			{
				min[0] = v.x();
			}
			if(v.x() > max.x())
			{
				max[0] = v.x();
			}

			if(v.y() < min.y())
			{
				min[1] = v.y();
			}
			if(v.y() > max.y())
			{
				max[1] = v.y();
			}

			if(v.z() < min.z())
			{
				min[2] = v.z();
			}
			if(v.z() > max.z())
			{
				max[2] = v.z();
			}
		}
	}

	this->boundingBox = Rectangle3(min, max);
}
void Model::setBoundingBox(Rectangle3 boundingBox)
{
	this->boundingBox = boundingBox;
}
