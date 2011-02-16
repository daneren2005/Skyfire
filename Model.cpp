#include "Model.h"

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
void Model::setBoundingBox(Rectangle3 boundingBox)
{
	this->boundingBox = boundingBox;
}
