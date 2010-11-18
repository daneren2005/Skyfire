/* 
 * File:   Mesh.cpp
 * Author: scott
 * 
 * Created on September 29, 2010, 4:04 PM
 */

#include "Mesh.h"

#include <iostream>

Mesh::Mesh() : Array<Triangle>()
{
	this->displayList = 0;
}

Mesh::Mesh(unsigned long size) : Array<Triangle>(size)
{
	this->displayList = 0;
}

Mesh::Mesh(const Mesh& orig) : Array<Triangle>(orig)
{
	this->displayList = 0;
}

Mesh::~Mesh()
{
	
}

void Mesh::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	if(this->displayList == 0)
	{
		this->displayList = glGenLists(1);
		glNewList(this->displayList, GL_COMPILE);
			glBegin(GL_TRIANGLES);
				for(int i = 0; i < _size; i++)
				{
					array[i].draw();
				}
			glEnd();
		glEndList();
	}
	else
	{
		glCallList(this->displayList);
	}
}

