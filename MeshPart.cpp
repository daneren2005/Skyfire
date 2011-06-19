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

#include "MeshPart.h"

#include <iostream>

MeshPart::MeshPart() : Array<Vertex>()
{
	this->wireFrame = false;
}
MeshPart::MeshPart(unsigned long size, bool wireFrame) : Array<Vertex>(size)
{
	this->wireFrame = wireFrame;
}

MeshPart::MeshPart(const MeshPart& orig) : Array<Vertex>(orig)
{
	this->wireFrame = orig.wireFrame;
	this->material = orig.material;
}

MeshPart::~MeshPart()
{
	
}

void MeshPart::draw()
{
	if(this->wireFrame)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glEnable(GL_LIGHTING);
		/*glEnable(GL_LIGHT1);

		// Setup light for scene
		float lightAmbient[] = {0.1f, 0.1f, 0.1f, 1.0f};
		glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);
		float lightSpec[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpec);
		float lightDiff[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiff);
		float lightPos[] = {0.0f, 0.0f, 1.0f, 0.0f};
		glLightfv(GL_LIGHT1, GL_POSITION, lightPos);*/

		// Setup light properties of material
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, this->material.ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, this->material.diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, this->material.specular);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, this->material.shininess);
	}

	// Draw vertices + normals + textures of mesh
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), this->array->position.getPointer());
	glNormalPointer(GL_FLOAT, sizeof(Vertex), this->array->normal.getPointer());
	glDrawArrays(GL_TRIANGLES, 0, this->used);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	glDisable(GL_LIGHTING);
}

Material MeshPart::getMaterial()
{
	return this->material;
}
void MeshPart::setMaterial(const Material& material)
{
	this->material = material;
}
float* MeshPart::getAmbientMaterial()
{
	return this->material.ambient;
}
void MeshPart::setAmbientMaterial(float r, float g, float b)
{
	this->material.ambient[0] = r;
	this->material.ambient[1] = g;
	this->material.ambient[2] = b;
}
float* MeshPart::getDiffuseMaterial()
{
	return this->material.diffuse;
}
void MeshPart::setDiffuseMaterial(float r, float g, float b)
{
	this->material.diffuse[0] = r;
	this->material.diffuse[1] = g;
	this->material.diffuse[2] = b;
}
float* MeshPart::getSpecularMaterial()
{
	return this->material.specular;
}
void MeshPart::setSpecularMaterial(float r, float g, float b)
{
	this->material.specular[0] = r;
	this->material.specular[1] = g;
	this->material.specular[2] = b;
}
float MeshPart::getShininess()
{
	return this->material.shininess;
}
void MeshPart::setShininess(float shine)
{
	this->material.shininess = shine;
}
float MeshPart::getTransparency()
{
	return this->material.transparency;
}
void MeshPart::setTransparency(float transparency)
{
	this->material.transparency = transparency;
}
float MeshPart::getRefraction()
{
	return this->material.refraction;
}
void MeshPart::setRefraction(float refraction)
{
	this->material.refraction = refraction;
}
float* MeshPart::getTransmissionFilter()
{
	return this->material.transmissionFilter;
}
void MeshPart::setTransmissionFilter(float r, float g, float b)
{
	this->material.transmissionFilter[0] = r;
	this->material.transmissionFilter[1] = g;
	this->material.transmissionFilter[2] = b;
}
Bitmap* MeshPart::getTextureMap()
{
	return this->material.textureMap;
}
void MeshPart::setTextureMap(Bitmap* bitmap)
{
	this->material.textureMap = bitmap;
}
Bitmap* MeshPart::getDiffuseMap()
{
	return this->material.diffuseMap;
}
void MeshPart::setDiffuseMap(Bitmap* bitmap)
{
	this->material.diffuseMap = bitmap;
}
Bitmap* MeshPart::getBumpMap()
{
	return this->material.bumpMap;
}
void MeshPart::setBumpMap(Bitmap* bitmap)
{
	this->material.bumpMap = bitmap;
}

void MeshPart::setWireFrame(bool option)
{
	this->wireFrame = option;
}