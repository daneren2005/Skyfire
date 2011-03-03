/*
 * File:   Region.cpp
 * Author: scott
 *
 * Created on July 14, 2010, 7:11 PM
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
