/* 
 * File:   Region.h
 * Author: scott
 *
 * Created on July 14, 2010, 7:11 PM
 */

#ifndef _REGION_H
#define	_REGION_H

#include "BaseObject.h"
#include "List.h"

class Region {
public:
	Region();
	Region(const Region& orig);
	virtual ~Region();

	virtual void update(double interval);
	virtual void draw(Vector cameraPosition, Vector cameraAngle);
protected:
	List<BaseObject*> objects;
};

#endif	/* _REGION_H */
