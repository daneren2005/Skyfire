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

#include "Texture.h"
#include "Console.h"
#include <string.h>

Texture::Texture(int width, int height)
{
	this->width = width;
	this->height = height;
	this->array = new unsigned char[width * height * 3];
	
	this->texture = 0;
}

Texture::Texture(const Texture& orig)
{
	this->width = orig.width;
	this->height = orig.height;
	this->array = new unsigned char[this->width * this->height * 3];
	memcpy(this->array, orig.array, width * height * 3);
	this->texture = orig.texture;
}

Texture::~Texture()
{
	delete this->array;
}

unsigned char* Texture::operator[](unsigned long row)
{
	return array + (width * row);
}

unsigned char* Texture::getPointer()
{
	return this->array;
}

GLuint Texture::getTexture()
{
	if(this->texture == 0)
	{
		// Initialize texture
		glEnable(GL_TEXTURE_2D);
		glGenTextures(1, &this->texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		// glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, array);
	}
	
	return this->texture;
}
