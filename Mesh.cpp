#include "Mesh.h"
#include "const.h"

Mesh::Mesh() : Array<MeshPart*>()
{
	
}

Mesh::Mesh(unsigned long size) : Array<MeshPart*>(size)
{
	
}

Mesh::Mesh(const Mesh& orig) : Array<MeshPart*>(orig)
{
	
}

Mesh::~Mesh()
{
	
}

long Mesh::numTriangles()
{
	long num;
	for(int i = 0; i < this->used; i++)
	{
		num += array[i]->size();
	}

	return num / 3;
}

void Mesh::draw()
{
	glDisable(GL_BLEND);

	// Draw bounding box outline
	// this->boundingBox.draw();

	for(int i = 0; i < this->used; i++)
	{
		array[i]->draw();
	}
}

AxisAlignedBox Mesh::getBoundingBox()
{
	return this->boundingBox;
}
void Mesh::computeBoundingBox()
{
	Vector min(MAXFLOAT, MAXFLOAT, MAXFLOAT);
	Vector max(MINFLOAT, MINFLOAT, MINFLOAT);
	for(int i = 0; i < this->used; i++)
	{
		MeshPart* mesh = array[i];
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

	this->boundingBox = AxisAlignedBox(min, max);
}
