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

#include "Region.h"

Region::Region()
{
	universe = NULL;
}

Region::Region(const Region& orig)
{
}

Region::~Region()
{
}

void Region::load()
{
	
}
void Region::load(const DataFile& world)
{	
	
}

void Region::update(double interval)
{
	BaseObject* object = NULL;
	for(List<BaseObject*>::Iterator it = objects.begin(); !it; it++)
	{
		object = it.value();
		object->update(interval);
	}
}

void Region::draw()
{
	BaseObject* object = NULL;
	for(List<BaseObject*>::Iterator it = objects.begin(); !it; it++)
	{
		object = it.value();
		object->draw();
	}
}

void Region::insertObject(BaseObject* object)
{
	this->objects.pushBack(object);
}
void Region::removeObject(BaseObject* object)
{
	try
	{
		this->objects.remove(object);
	}
	catch(...)
	{
		console << "Error Region::removeObject: Object not in region" << newline;
	}
}

BaseObject* Region::getFront()
{
	return objects.front();
}
