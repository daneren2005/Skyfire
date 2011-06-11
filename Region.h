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

#ifndef _REGION_H
#define	_REGION_H

#include "BaseObject.h"
#include "List.h"

class Universe;

class Region {
public:
	Region();
	Region(const Region& orig);
	virtual ~Region();

	virtual void update(double interval);
	virtual void draw();

	virtual void insertObject(BaseObject* object);
	virtual void removeObject(BaseObject* object);

	// temp
	BaseObject* getFront();

	friend class Camera;
	friend class Universe;
protected:
	Universe* universe;
	List<BaseObject*> objects;
};

#endif	/* _REGION_H */

