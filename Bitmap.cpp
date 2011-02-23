/* 
 * File:   Bitmap.cpp
 * Author: scott
 * 
 * Created on February 22, 2011, 4:00 PM
 */

#include "Bitmap.h"

Bitmap::Bitmap(int width, int height)
{
	this->width = width;
	this->height = height;
	this->array = new int(width * height);
}

Bitmap::Bitmap(const Bitmap& orig)
{
	this->width = orig.width;
	this->height = orig.height;
	this->array = new int(this->width * this->height);
	for(int i = 0; i < (width * height); i++)
	{
		this->array[i] = orig.array[i];
	}
}

Bitmap::~Bitmap()
{
	delete this->array;
}

