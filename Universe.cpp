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
		region = regions.pop_front();
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

	// Update all regions
	Region* region = NULL;
	for(Iterator<Region*> it = uni->regions.begin(false); !it; it++)
	{
		region = it.value();
		region->update(interval);
	}

	// If input is set, do stuff with it
	if(uni->input != NULL)
	{
		if(uni->input->moveLeft && !uni->input->moveRight)
			uni->camera->moveByAbsolute(-interval * 10, 0.0f, 0.0f);
		if(!uni->input->moveLeft && uni->input->moveRight)
			uni->camera->moveByAbsolute(interval * 10, 0.0f, 0.0f);

		if(uni->input->moveUp && !uni->input->moveDown)
			uni->camera->moveByAbsolute(0.0f, interval * 10, 0.0f);
		if(!uni->input->moveUp && uni->input->moveDown)
			uni->camera->moveByAbsolute(0.0f, -interval * 10, 0.0f);

		if(uni->input->moveIn && !uni->input->moveOut)
			uni->camera->moveByAbsolute(0.0f, 0.0f, -interval * 10);
		if(!uni->input->moveIn && uni->input->moveOut)
			uni->camera->moveByAbsolute(0.0f, 0.0f, interval * 10);

		if(uni->input->rotateLeft && !uni->input->rotateRight)
			uni->camera->rotateByAbsolute(-interval * 100.0f, 0.0f, 0.0f);
		if(!uni->input->rotateLeft && uni->input->rotateRight)
			uni->camera->rotateByAbsolute(interval * 100.0f, 0.0f, 0.0f);

		if(uni->input->rotateUp && !uni->input->rotateDown)
			uni->camera->rotateByAbsolute(0.0f, interval * 100.0f, 0.0f);
		if(!uni->input->rotateUp && uni->input->rotateDown)
			uni->camera->rotateByAbsolute(0.0f, -interval * 100.0f, 0.0f);
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
	this->regions.push_front(region);
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
