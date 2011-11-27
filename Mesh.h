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

#ifndef _MESH_H
#define	_MESH_H

#include "Model.h"
#include "MeshPart.h"
#include "AxisAlignedBox.h"
#include "Triangle.h"

class Mesh : public Model
{
public:
	Mesh();
	Mesh(unsigned long size);
	Mesh(const Mesh& orig);
	virtual ~Mesh();

	void insert(MeshPartPointer mesh);
	long size();

	virtual void computeBoundingBox();
	virtual AxisAlignedBox getBoundingBox();

	virtual void draw();
	virtual void drawFrame();
	virtual long numTriangles();
	
	virtual float getRayIntersection(const Ray& ray, const Matrix4& transform);
	virtual float getRayIntersection(Vector s, Vector r);
private:
	Array<MeshPartPointer> meshParts;
	AxisAlignedBox boundingBox;
};

typedef SharedPointer<Mesh> MeshPointer;

#endif
