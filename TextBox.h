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

#ifndef TEXTBOX_H
#define	TEXTBOX_H

#include "Renderer.h"
#include "Font2D.h"
#include "Vector.h"

class TextBox : public Renderer
{
public:
	TextBox();
	TextBox(int x, int y);
	TextBox(const String& str, int x, int y);
	TextBox(const TextBox& orig);
	virtual ~TextBox();
	
	String getString();
	void setString(const String& str);
	int getX();
	int getY();
	Rectangle2 getArea();
	void setPosition(int x, int y);
	Vector getColor();
	void setColor(const Vector& color);
	Font2D getFont();
	void setFont(Font2D font);
	
	virtual void render();
private:
	int x, y;
	String str;
	Vector color;
	Font2D font;
};

#endif	/* TEXTBOX_H */

