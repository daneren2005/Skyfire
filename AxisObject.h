#ifndef _AXISOBJECT_H
#define	_AXISOBJECT_H

#include "BaseObject.h"

class AxisObject : public BaseObject
{
public:
	AxisObject();
	AxisObject(float x, float y, float z);
	AxisObject(const AxisObject& orig);
	virtual ~AxisObject();

	virtual void update(double interval);
};

#endif	/* _AXISOBJECT_H */