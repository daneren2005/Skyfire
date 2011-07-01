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

#ifndef _UNIVERSE_H
#define	_UNIVERSE_H

#include "Region.h"
#include "Camera.h"
#include "List.h"
#include "StopWatch.h"
#include "Input.h"
#include "Thread.h"

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

	friend class Region;
protected:
	bool quit;

	List<Region*> regions;
	Region* activeRegion;
	Camera* camera;

	Input* input;

	// Update thread + loop
	bool running;
	StopWatch timer;
	Thread updateThread;
	static void* updateFunction(Thread* arg);
};

#endif	/* _UNIVERSE_H */

