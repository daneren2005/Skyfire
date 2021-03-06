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

#ifndef _TEXTURE_H
#define	_TEXTURE_H

#include <GL/gl.h>

class Texture
{
public:
	Texture(int width, int height);
	Texture(const Texture& orig);
	virtual ~Texture();

	unsigned char* operator[](unsigned long row);
	unsigned char* getPointer();
	GLuint getTexture();
private:
	int width, height;
	unsigned char* array;
	GLuint texture;
};

#endif	/* _BITMAP_H */

