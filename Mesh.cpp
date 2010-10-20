/* 
 * File:   Mesh.cpp
 * Author: scott
 * 
 * Created on September 29, 2010, 4:04 PM
 */

#include "Mesh.h"

#include <iostream>

Mesh::Mesh() : Array()
{
	this->displayList = 0;
}

Mesh::Mesh(unsigned long triangles) : Array(triangles)
{
	this->displayList = 0;
}

Mesh::Mesh(const Mesh& orig) : Array(orig)
{
	this->displayList = 0;
}

Mesh::~Mesh()
{
	
}

void Mesh::draw()
{
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

