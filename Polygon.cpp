/* 
 * File:   Polygon.cpp
 * Author: scott
 * 
 * Created on September 29, 2010, 4:04 PM
 */

#include "Polygon.h"

#include <iostream>

Polygon::Polygon()
{
	this->displayList = 0;
}

Polygon::Polygon(const Polygon& orig)
{

}

Polygon::~Polygon()
{
	
}

void Polygon::addTriangle(Triangle* triangle)
{
	triangles.push_back(triangle);
}

void Polygon::draw()
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

