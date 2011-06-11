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

#include "MeshPart.h"
#include "AxisAlignedBox.h"

class Mesh : public Array<MeshPart*>
{
public:
	Mesh();
	Mesh(unsigned long size);
	Mesh(const Mesh& orig);
	virtual ~Mesh();

	AxisAlignedBox getBoundingBox();
	void computeBoundingBox();

	long numTriangles();

	void draw();
private:
	AxisAlignedBox boundingBox;
};

#endif
