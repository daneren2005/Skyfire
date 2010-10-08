/* 
 * File:   Universe.h
 * Author: scott
 *
 * Created on July 14, 2010, 7:11 PM
 */

#ifndef _UNIVERSE_H
#define	_UNIVERSE_H

#include "Region.h"
#include "Camera.h"
#include <pthread.h>
#include "List.h"
#include "StopWatch.h"
#include "Input.h"
#include "Rate.h"

class Universe
{
public:
	Universe();
	Universe(const Universe& orig);
	virtual ~Universe();

	virtual void load();
	virtual void start();
	virtual void resume();
	virtual void pause();
	
	Camera* getCamera();
	void addRegion(Region* region);
	void setActiveRegion(Region* region);

	void setInput(Input* input);

	double runningTime();
protected:
	bool quit;

	List<Region*> regions;
	Region* activeRegion;
	Camera* camera;

	Input* input;

	// Update thread + loop
	Rate updateRate;
	bool running;
	StopWatch timer;
	pthread_t updateThread;
	pthread_mutex_t updateLock;
	static void* updateLoop(void* arg);
	void update();
};

#endif	/* _UNIVERSE_H */

