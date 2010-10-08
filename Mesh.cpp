/* 
 * File:   Mesh.cpp
 * Author: scott
 * 
 * Created on September 29, 2010, 4:04 PM
 */

#include "Mesh.h"

#include <iostream>

Mesh::Mesh()
{
	this->displayList = 0;
}

Mesh::Mesh(const Mesh& orig)
{

}

Mesh::~Mesh()
{
	
}

void Mesh::addTriangle(Triangle* triangle)
{
	triangles.push_back(triangle);
}

void Mesh::draw()
{
	if(this->displayList == 0)
	{
		this->displayList = glGenLists(1);
		glNewList(this->displayList, GL_COMPILE);
			glBegin(GL_TRIANGLES);
				for(Iterator<Triangle*> it = triangles.begin(false); !it; it++)
				{
					Triangle* triangle = it.value();
					triangle->draw();
				}
			glEnd();
		glEndList();
	}
	else
	{
		glCallList(this->displayList);
	}
}

