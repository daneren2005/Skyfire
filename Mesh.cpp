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
#include "Vector.h"
#include <float.h>

Mesh::Mesh() : Model()
{
	
}

Mesh::Mesh(unsigned long size) : Model()
{
	meshParts = Array<MeshPartPointer>(size);
}

Mesh::Mesh(const Mesh& orig) : Model(orig)
{
	meshParts = orig.meshParts;
}

Mesh::~Mesh()
{
	
}

void Mesh::insert(MeshPartPointer mesh)
{
	meshParts.insert(mesh);
}
long Mesh::size()
{
	return meshParts.size();
}

void Mesh::computeBoundingBox()
{
	Vector minV(FLT_MAX, FLT_MAX, FLT_MAX);
	Vector maxV(FLT_MIN, FLT_MIN, FLT_MIN);
	for(unsigned int i = 0; i < meshParts.size(); i++)
	{
		MeshPartPointer mesh = meshParts[i];
		for(unsigned int j = 0; j < mesh->size(); j++)
		{
			Vector v = (*mesh)[j].position;
			if(v.x() < minV.x())
			{
				minV[0] = v.x();
			}
			if(v.x() > maxV.x())
			{
				maxV[0] = v.x();
			}

			if(v.y() < minV.y())
			{
				minV[1] = v.y();
			}
			if(v.y() > maxV.y())
			{
				maxV[1] = v.y();
			}

			if(v.z() < minV.z())
			{
				minV[2] = v.z();
			}
			if(v.z() > maxV.z())
			{
				maxV[2] = v.z();
			}
		}
	}

	this->boundingBox = AxisAlignedBox(minV, maxV);
}
AxisAlignedBox Mesh::getBoundingBox()
{
	return this->boundingBox;
}

void Mesh::draw()
{
	glDisable(GL_BLEND);

	// Draw bounding box outline
	// this->boundingBox.draw();

	for(unsigned int i = 0; i < meshParts.size(); i++)
	{
		meshParts[i]->draw();
	}
}
void Mesh::drawFrame()
{
	for(unsigned int i = 0; i < meshParts.size(); i++)
	{
		meshParts[i]->drawFrame();
	}
}

long Mesh::numTriangles()
{
	long num = 0;
	for(unsigned int i = 0; i < meshParts.size(); i++)
	{
		num += meshParts[i]->size();
	}

	return num / 3;
}
float Mesh::getRayIntersection(const Ray& ray, const Matrix4& transform)
{
	float minT = 100000.0f;
	
	for(ulong i = 0; i < meshParts.size(); i++)
	{
		MeshPartPointer meshPart = meshParts[i];
		for(ulong j = 0; j + 3 < meshPart->size(); j += 3)
		{
			// console << (transform * meshPart->get(j).position) << "  " << (transform * meshPart->get(j + 1).position) << "  " << (transform * meshPart->get(j + 2).position) << newline;
			float t = ray.getIntersection(transform * meshPart->get(j).position, transform * meshPart->get(j+1).position, transform * meshPart->get(j+2).position);
			if(t > 0.0f)
				return t;
		}
	}
	
	return (minT != 100000.0f) ? minT : -1.0f;
}
float Mesh::getRayIntersection(Vector s, Vector r)
{
	float minT = 100000.0f;
	
	for(ulong i = 0; i < meshParts.size(); i++)
	{
		MeshPartPointer meshPart = meshParts[i];
		for(ulong j = 0; j + 3 < meshPart->size(); j += 3)
		{
			Triangle triangle(meshPart->get(i).position, meshPart->get(i+1).position, meshPart->get(i+2).position);
			float t = triangle.getRayIntersection(s, r);
			if(t > 0.0f && t < minT)
				minT = t;
		}
	}
	
	return (minT != 100000.0f) ? minT : -1.0f;
}
