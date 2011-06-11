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

#include "Bitmap.h"
#include "Console.h"

Bitmap::Bitmap(int width, int height)
{
	this->width = width;
	this->height = height;
	this->array = new unsigned char(width * height);
}

Bitmap::Bitmap(const Bitmap& orig)
{
	this->width = orig.width;
	this->height = orig.height;
	this->array = new unsigned char(this->width * this->height * 3);
	for(int i = 0; i < (width * height * 3); i++)
	{
		this->array[i] = orig.array[i];
	}
}

Bitmap::~Bitmap()
{
	delete this->array;
}

unsigned char* Bitmap::operator[](unsigned long row)
{
	return array + (width * row);
}

unsigned char* Bitmap::getPointer()
{
	return this->array;
}
