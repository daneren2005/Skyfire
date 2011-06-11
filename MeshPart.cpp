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

void MeshPart::setWireFrame(bool option)
{
	this->wireFrame = option;
}
