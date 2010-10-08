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
	pthread_mutex_init(&this->updateLock, NULL);

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
	pthread_create(&this->updateThread, NULL, updateLoop, (void*)this);
}
void Universe::resume()
{
	if(running == false)
	{
		timer.start();
		pthread_mutex_unlock(&this->updateLock);
		running = true;
	}
}
void Universe::pause()
{
	if(running == true)
	{
		timer.stop();
		pthread_mutex_lock(&this->updateLock);
		running = false;
	}
}

void* Universe::updateLoop(void* arg)
{
	Universe* uni = (Universe*)arg;

	while(uni->quit == false)
	{
		// Try to lock in order to run update
		pthread_mutex_lock(&uni->updateLock);
		uni->update();
		pthread_mutex_unlock(&uni->updateLock);
	}

	// Doesn't compile without returning something
	#ifdef WIN32
		return NULL;
	#endif
}

void Universe::update()
{
	updateRate.executeStart();

	float interval = (float)timer.elapsedTime();

	// Update all regions
	Region* region = NULL;
	for(Iterator<Region*> it = regions.begin(false); !it; it++)
	{
		region = it.value();
		region->update(interval);
	}

	// If input is set, do stuff with it
	if(this->input != NULL)
	{
		if(this->input->moveLeft && !this->input->moveRight)
			camera->moveByAbsolute(-interval * 10, 0.0f, 0.0f);
		if(!this->input->moveLeft && this->input->moveRight)
			camera->moveByAbsolute(interval * 10, 0.0f, 0.0f);

		if(this->input->moveUp && !this->input->moveDown)
			camera->moveByAbsolute(0.0f, interval * 10, 0.0f);
		if(!this->input->moveUp && this->input->moveDown)
			camera->moveByAbsolute(0.0f, -interval * 10, 0.0f);

		if(this->input->moveIn && !this->input->moveOut)
			camera->moveByAbsolute(0.0f, 0.0f, -interval * 10);
		if(!this->input->moveIn && this->input->moveOut)
			camera->moveByAbsolute(0.0f, 0.0f, interval * 10);

		if(this->input->rotateLeft && !this->input->rotateRight)
			camera->rotateByAbsolute(-interval * 100.0f, 0.0f, 0.0f);
		if(!this->input->rotateLeft && this->input->rotateRight)
			camera->rotateByAbsolute(interval * 100.0f, 0.0f, 0.0f);

		if(this->input->rotateUp && !this->input->rotateDown)
			camera->rotateByAbsolute(0.0f, interval * 100.0f, 0.0f);
		if(!this->input->rotateUp && this->input->rotateDown)
			camera->rotateByAbsolute(0.0f, -interval * 100.0f, 0.0f);
	}

	updateRate.executeEnd();
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
