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
	for(int i = 0; i < this->used; i++)
	{
		array[i]->draw();
	}
}
