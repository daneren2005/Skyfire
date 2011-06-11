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

Rectangle::Rectangle()
{
	this->lx = 0;
	this->ly = 0;
	this->ux = 0;
	this->uy = 0;
}
Rectangle::Rectangle(int lx, int ly, int ux, int uy)
{
	this->lx = lx;
	this->ly = ly;
	this->ux = ux;
	this->uy = uy;
}

Rectangle::~Rectangle()
{
}
