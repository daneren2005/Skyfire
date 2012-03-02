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

#include "Universe.h"
#include "MemberFunction.h"

Universe::Universe()
{
	this->running = false;
	this->camera = new Camera();
	updateThread.setTicksPerSecond(60);
}

Universe::Universe(const Universe& orig)
{
}

Universe::~Universe()
{
	this->running = false;
	updateThread.stop();
	
	Region* region = NULL;
	while(regions.size() > 0)
	{
		region = regions.popFront();
		delete region;
	}
}

void Universe::start()
{
	this->running = true;
	MemberFunction<Universe, void, Thread*> func(this);
	func = &Universe::updateFunction;
	updateThread.start(func, this);
}
void Universe::resume()
{
	if(running == false)
	{
		running = true;
		updateThread.resume();
	}
}
void Universe::pause()
{
	if(running == true)
	{
		running = false;
		updateThread.pause();
	}
}

void Universe::updateFunction(Thread* arg)
{
	float interval = (float)updateThread.getTimeSinceTick();

	// Update all regions
	for(List<Region*>::Iterator it = regions.begin(); !it; it++)
	{
		it.value()->update(interval);
	}
}

Camera* Universe::getCamera()
{
	return this->camera;
}

void Universe::addRegion(Region* region)
{
	region->universe = this;
	this->regions.pushFront(region);
}

void Universe::setActiveRegion(Region* region)
{
	// TODO: check if region is in list, if not add it?
	this->activeRegion = region;
	this->camera->setActiveRegion(region);
}

double Universe::runningTime()
{
	return updateThread.getRunningTime();
}
