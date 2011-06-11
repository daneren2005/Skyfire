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

