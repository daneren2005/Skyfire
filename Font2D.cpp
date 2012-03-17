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

#include "Font2D.h"

#include "Window.h"

Font2D::Font2D()
{
	list = 0;
}
Font2D::Font2D(String name, int size)
{
	this->name = name;
	this->size = size;
	HFONT fontObj;
	list = glGenLists(128);
	fontObj = CreateFont(size, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE | DEFAULT_PITCH, name.cStr());
	SelectObject(_defaultCallback->device, fontObj);
	wglUseFontBitmaps(_defaultCallback->device, 0, 128, list);
	DeleteObject(fontObj);
	glListBase(list);
}

Font2D::Font2D(const Font2D& orig)
{
	this->list = orig.list;
	this->name = orig.name;
	this->size = orig.size;
}

Font2D::~Font2D()
{
}

void Font2D::draw(String str)
{
	glListBase(list);
	glCallLists(str.length(), GL_UNSIGNED_BYTE, str.cStr());
}

