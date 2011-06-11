/*
	This file is part of Skyfire.

    Skyfire is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Skyfire is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Skyfire.  If not, see <http://www.gnu.org/licenses/>.
*/

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
	long num = 0;
	for(int i = 0; i < this->used; i++)
	{
		console << array[i]->size() << newline;
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
