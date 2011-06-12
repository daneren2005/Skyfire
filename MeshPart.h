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
#include "Material.h"
#include "SharedPointer.h"

struct Vertex
{
	Vector position;
	Vector normal;
	Vector texture;
};

class MeshPart : public Array<Vertex>
{
public:
	MeshPart();
	MeshPart(unsigned long size, bool wireFrame = false);
	MeshPart(const MeshPart& orig);
	virtual ~MeshPart();

	void draw();

	Material getMaterial();
	void setMaterial(const Material& material);
	float* getAmbientMaterial();
	void setAmbientMaterial(float r, float g, float b);
	float* getDiffuseMaterial();
	void setDiffuseMaterial(float r, float g, float b);
	float* getSpecularMaterial();
	void setSpecularMaterial(float r, float g, float b);
	float getShininess();
	void setShininess(float shine);
	float getTransparency();
	void setTransparency(float transparency);
	float getRefraction();
	void setRefraction(float refraction);
	float* getTransmissionFilter();
	void setTransmissionFilter(float r, float g, float b);
	Bitmap* getTextureMap();
	void setTextureMap(Bitmap* bitmap);
	Bitmap* getDiffuseMap();
	void setDiffuseMap(Bitmap* bitmap);
	Bitmap* getBumpMap();
	void setBumpMap(Bitmap* bitmap);

	void setWireFrame(bool option);
private:
	Material material;
	bool wireFrame;
};

typedef SharedPointer<MeshPart> MeshPartPointer;

#endif	/* _MeshPart_H */

