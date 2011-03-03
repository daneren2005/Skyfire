/* 
 * File:   Bitmap.h
 * Author: scott
 *
 * Created on February 22, 2011, 4:00 PM
 */

#ifndef _BITMAP_H
#define	_BITMAP_H

class Bitmap
{
public:
	Bitmap(int width, int height);
	Bitmap(const Bitmap& orig);
	virtual ~Bitmap();

	unsigned char* operator[](unsigned long row);
	unsigned char* getPointer();
private:
	int width;
	int height;
	unsigned char* array;
};

#endif	/* _BITMAP_H */

