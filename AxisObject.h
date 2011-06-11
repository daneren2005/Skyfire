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
	virtual void draw();

	virtual void load();
};

#endif	/* _AXISOBJECT_H */
