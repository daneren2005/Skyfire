/* 
 * File:   AnimateObject.h
 * Author: scott
 *
 * Created on January 11, 2011, 1:05 PM
 */

#ifndef _ANIMATEOBJECT_H
#define	_ANIMATEOBJECT_H

#include "BaseObject.h"

class AnimateObject : public BaseObject
{
public:
	AnimateObject();
	AnimateObject(float x, float y, float z);
	AnimateObject(const AnimateObject& orig);
	virtual ~AnimateObject();
protected:
	
private:

};

#endif	/* _ANIMATEOBJECT_H */

