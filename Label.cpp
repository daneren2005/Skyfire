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

#include "Label.h"

Label::Label()
{
	this->str = "";
	this->color = Vector(0.0f, 0.0f, 0.0f);
}
Label::Label(const String& str)
{
	this->str = str;
	this->color = Vector(0.0f, 0.0f, 0.0f);
}
Label::Label(int x, int y)
{
	this->screenArea = Rectangle2(x, y, x, y);
	this->color = Vector(0.0f, 0.0f, 0.0f);
}
Label::Label(const String& str, int x, int y)
{
	this->screenArea = Rectangle2(x, y, x, y);
	this->str = str;
	this->color = Vector(0.0f, 0.0f, 0.0f);
}

Label::Label(const Label& orig)
{
	this->str = orig.str;
	this->screenArea = orig.screenArea;
	this->color = orig.color;
}

Label::~Label()
{
}

String Label::getString()
{
	return str;
}
void Label::setString(const String& str)
{
	this->str = str;
}
int Label::getX()
{
	return screenArea.lx;
}
int Label::getY()
{
	return screenArea.ly;
}
Rectangle2 Label::getArea()
{
	return screenArea;
}
void Label::setPosition(int x, int y)
{
	screenArea.lx = x;
	screenArea.ly = y;
}
Vector Label::getColor()
{
	return color;
}
void Label::setColor(const Vector& color)
{
	this->color = color;
}

void Label::render()
{	
	glColor3f(color[0], color[1], color[2]);
	glRasterPos2i(screenArea.lx, screenArea.ly);
	glCallLists(str.length(), GL_UNSIGNED_BYTE, str.cStr());
}

