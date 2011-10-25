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

Universe::Universe()
{
	this->quit = false;
	this->running = false;
	this->camera = new Camera();
	this->input = NULL;
}

Universe::Universe(const Universe& orig)
{
}

Universe::~Universe()
{
	delete this->input;
	delete this->camera;

	Region* region = NULL;
	while(regions.size() > 0)
	{
		region = regions.popFront();
		delete region;
	}
}

void Universe::load()
{
	
}

void Universe::start()
{
	this->running = true;
	this->timer.start();
	updateThread.setTicksPerSecond(60);
	updateThread.start(updateFunction, this);
}
void Universe::resume()
{
	if(running == false)
	{
		timer.start();
		running = true;
		updateThread.resume();
	}
}
void Universe::pause()
{
	if(running == true)
	{
		timer.stop();
		running = false;
		updateThread.pause();
	}
}

void Universe::updateFunction(Thread* arg)
{
	Thread* thread = (Thread*)arg;
	Universe* uni = (Universe*)thread->getArg();

	float interval = (float)uni->timer.elapsedTime();

	if(uni->input != NULL)
	{
		uni->input->update(interval);
	}

	// Update all regions
	Region* region = NULL;
	for(List<Region*>::Iterator it = uni->regions.begin(); !it; it++)
	{
		region = it.value();
		region->update(interval);
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
	return timer.totalTime();
}

void Universe::setInput(Input* input)
{
	this->input = input;
}
