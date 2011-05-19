/* 
 * File:   StaticObject.h
 * Author: scott
 *
 * Created on January 11, 2011, 1:17 PM
 */

#ifndef _STATICOBJECT_H
#define	_STATICOBJECT_H

#include "BaseObject.h"
#include "Camera.h"
#include "Region.h"

class StaticObject : public BaseObject
{
public:
	StaticObject();
	StaticObject(float x, float y, float z);
	StaticObject(const StaticObject& orig);
	virtual ~StaticObject();

	virtual void draw();
	virtual AxisAlignedBox getBoundingBox();
protected:
	Model* model;
private:

};

#endif	/* _STATICOBJECT_H */

