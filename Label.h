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

#ifndef LABEL_H_
#define	LABEL_H_

#include "Renderer.h"
#include "Vector.h"

class Label : public Renderer
{
public:
	Label();
	Label(const String& str);
	Label(int x, int y);
	Label(const String& str, int x, int y);
	Label(const Label& orig);
	virtual ~Label();
	
	String getString();
	void setString(const String& str);
	int getX();
	int getY();
	Rectangle2 getArea();
	void setPosition(int x, int y);
	Vector getColor();
	void setColor(const Vector& color);
	
	virtual void render();
private:
	String str;
	Vector color;
};

#endif	/* LABEL_H */

