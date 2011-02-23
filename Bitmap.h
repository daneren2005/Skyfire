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
private:
	int width;
	int height;
	int* array;
};

#endif	/* _BITMAP_H */

