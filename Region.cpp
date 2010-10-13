/*
 * File:   Region.cpp
 * Author: scott
 *
 * Created on July 14, 2010, 7:11 PM
 */

#include "Region.h"

Region::Region()
{

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
	for(Iterator<BaseObject*> it = objects.begin(false); !it; it++)
	{
		object = it.value();
		object->update(interval);
	}
}

void Region::draw()
{
	BaseObject* object = NULL;
	for(Iterator<BaseObject*> it = objects.begin(false); !it; it++)
	{
		object = it.value();
		object->draw();
	}
}
