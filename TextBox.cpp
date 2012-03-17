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

#include "TextBox.h"
#include "Window.h"

TextBox::TextBox()
{
	this->str = "";
	this->color = Vector(0.0f, 0.0f, 0.0f);
	font = _defaultCallback->getDefaultFont();
}
TextBox::TextBox(int x, int y)
{
	this->str = "";
	this->screenArea.lx = x;
	this->screenArea.ly = y;
	this->screenArea.ux = x + 20;
	this->screenArea.uy = y - 10;
	this->x = x + 2;
	this->y = y - 2;
	font = _defaultCallback->getDefaultFont();
	this->color = Vector(0.0f, 0.0f, 0.0f);
}
TextBox::TextBox(const String& str, int x, int y)
{
	this->str = str;
	this->screenArea.lx = x;
	this->screenArea.ly = y;
	this->screenArea.ux = x + 20;
	this->screenArea.uy = y - 14;
	this->color = Vector(0.0f, 0.0f, 0.0f);
	this->x = x + 2;
	this->y = y - 2;
	font = _defaultCallback->getDefaultFont();
	this->color = Vector(0.0f, 0.0f, 0.0f);
}

TextBox::TextBox(const TextBox& orig)
{
	this->str = orig.str;
	this->screenArea = orig.screenArea;
	this->color = orig.color;
	this->font = orig.font;
	this->x = orig.x;
	this->y = orig.y;
}

TextBox::~TextBox()
{
}

String TextBox::getString()
{
	return str;
}
void TextBox::setString(const String& str)
{
	this->str = str;
}
int TextBox::getX()
{
	return screenArea.lx;
}
int TextBox::getY()
{
	return screenArea.ly;
}
Rectangle2 TextBox::getArea()
{
	return screenArea;
}
void TextBox::setPosition(int x, int y)
{
	this->screenArea.lx = x;
	this->screenArea.ly = y;
	this->screenArea.ux = x + 20;
	this->screenArea.uy = y - 14;
}
Vector TextBox::getColor()
{
	return color;
}
void TextBox::setColor(const Vector& color)
{
	this->color = color;
}
Font2D TextBox::getFont()
{
	return this->font;
}
void TextBox::setFont(Font2D font)
{
	this->font = font;
}

void TextBox::render()
{
	glColor3f(color[0], color[1], color[2]);
	screenArea.draw();
	glRasterPos2i(x, y);
	font.draw(str);
}

