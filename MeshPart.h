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

#ifndef _MeshPart_H
#define	_MeshPart_H

#include "Array.h"
#include "Triangle.h"
#include "Bitmap.h"
#include "Vector.h"

struct Vertex
{
	Vector position;
	Vector normal;
	Vector texture;
};

struct Material
{
	float ambient[3];
	float diffuse[3];
	float specular[3];
	float shininess;
	float transparency; // 1 = normal, 0 = transparent
	float refraction; // 1 = light doesnt bend, > 1 = light bends
	float transmissionFiler[3]; // light filter for rgb, 1 = allows, 0 = disallows
	Bitmap* diffuseMap;
	Bitmap* bumpMap;
};

class MeshPart : public Array<Vertex>
{
public:
	MeshPart();
	MeshPart(unsigned long size, bool wireFrame = false);
	MeshPart(const MeshPart& orig);
	virtual ~MeshPart();

	void draw();

	Material material;
	void setWireFrame(bool option);
private:
	bool wireFrame;
};

#endif	/* _MeshPart_H */

