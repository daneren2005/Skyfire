/* 
 * File:   Universe.cpp
 * Author: scott
 * 
 * Created on July 14, 2010, 7:11 PM
 */

#include "Universe.h"

Universe::Universe()
{
	this->quit = false;
	this->running = false;
	this->camera = new Camera();
	this->input = NULL;

	this->updateRate = Rate(60);
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

void* Universe::updateFunction(void* arg)
{
	Thread* thread = (Thread*)arg;
	Universe* uni = (Universe*)thread->getArg();

	uni->updateRate.executeStart();

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

	uni->updateRate.executeEnd();

	return NULL;
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
