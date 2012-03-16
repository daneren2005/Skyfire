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

#include "Rectangle.h"

#include <GL/gl.h>
#include <GL/glu.h>

Rectangle2::Rectangle2()
{
	this->lx = 0;
	this->ly = 0;
	this->ux = 0;
	this->uy = 0;
}
Rectangle2::Rectangle2(int lx, int ly, int ux, int uy)
{
	this->lx = lx;
	this->ly = ly;
	this->ux = ux;
	this->uy = uy;
}

Rectangle2::~Rectangle2()
{
}

void Rectangle2::draw()
{
	glBegin(GL_LINES);
		glVertex2i(lx, ly);
		glVertex2i(lx, uy);
		glVertex2i(lx, uy);
		glVertex2i(ux, uy);
		glVertex2i(ux, uy);
		glVertex2i(ux, ly);
		glVertex2i(ux, ly);
		glVertex2i(lx, ly);
	glEnd();
}
