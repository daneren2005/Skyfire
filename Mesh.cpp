/* 
 * File:   Mesh.cpp
 * Author: scott
 * 
 * Created on September 29, 2010, 4:04 PM
 */

#include "Mesh.h"

#include <iostream>

Mesh::Mesh() : Array<Vertex>()
{
	this->wireFrame = false;
}
Mesh::Mesh(unsigned long size, bool wireFrame) : Array<Vertex>(size)
{
	this->wireFrame = wireFrame;
}

Mesh::Mesh(const Mesh& orig) : Array<Vertex>(orig)
{
	this->wireFrame = orig.wireFrame;
}

Mesh::~Mesh()
{
	
}

void Mesh::draw()
{
	if(this->wireFrame)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	/*this->displayList = glGenLists(1);
	glNewList(this->displayList, GL_COMPILE);
		glBegin(GL_TRIANGLES);
			glColor3f(1.0f, 0.0f, 0.0f);
			for(int i = 0; i < _size; i += 3)
			{
				glVertex3f(array[i], array[i + 1], array[i + 2]);
			}
		glEnd();
	glEndList();*/

	glEnable(GL_LIGHTING);

	// Setup light for scene
	float lightDif[] = {0.1f, 0.1f, 0.1f, 1.0f};
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightDif);
	float lightSpec[] = {1.0f, 1.0f, 1.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec);
	float lightPos[] = {0.0f, 0.0f, 1.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	// glMateriali(GL_FRONT, GL_SHININESS, 128);
	glEnable(GL_LIGHT0);

	// Setup light properties of material
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, this->material.ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, this->material.diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, this->material.specular);

	// Draw vertices + normals + textures of mesh
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), this->array);
	glDrawArrays(GL_TRIANGLES, 0, this->_size);
	glDisableClientState(GL_VERTEX_ARRAY);

	glDisable(GL_LIGHTING);
}
