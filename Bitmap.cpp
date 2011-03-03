/* 
 * File:   Bitmap.cpp
 * Author: scott
 * 
 * Created on February 22, 2011, 4:00 PM
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
