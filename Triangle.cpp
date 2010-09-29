/* 
 * File:   Triangle.cpp
 * Author: scott
 * 
 * Created on September 29, 2010, 4:06 PM
 */

#include "Triangle.h"

Triangle::Triangle()
{
	
}
Triangle::Triangle(Vector a, Vector b, Vector c, Vector color)
{
	vertex[0] = a;
	vertex[1] = b;
	vertex[2] = c;
	this->color = color;
}

Triangle::Triangle(const Triangle& orig)
{

}

Triangle::~Triangle()
{
	
}

void Triangle::draw()
{
	glColor3f(this->color[0], this->color[1], this->color[2]);
	glVertex3f(this->vertex[0][0], this->vertex[0][1], this->vertex[0][2]);
	glVertex3f(this->vertex[1][0], this->vertex[1][1], this->vertex[1][2]);
	glVertex3f(this->vertex[2][0], this->vertex[2][1], this->vertex[2][2]);
}

