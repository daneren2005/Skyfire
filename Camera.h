/* 
 * File:   RegionScene.h
 * Author: scott
 *
 * Created on July 14, 2010, 8:21 PM
 */

#ifndef _CAMERA_H
#define	_CAMERA_H

#include "Scene.h"
#include "Region.h"
#include "BaseObject.h"

class Camera : public Scene, public BaseObject
{
public:
	Camera();
	Camera(const Camera& orig);
	virtual ~Camera();

	void setActiveRegion(Region* region);
	virtual void render();
	virtual void update(double interval);
private:
	Region* activeRegion;
};

#endif	/* _CAMERA_H */

