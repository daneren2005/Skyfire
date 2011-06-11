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

