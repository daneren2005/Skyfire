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

class Universe;

class Camera : public Scene, public BaseObject
{
public:
	Camera();
	Camera(const Camera& orig);
	virtual ~Camera();

	virtual void rotateBy(float x, float y, float z);
	virtual void rotateBy(const Vector& amount);

	void setActiveObject(BaseObject* object);
	void setActiveRegion(Region* region);
	Region* getActiveRegion();
	virtual void render();
	virtual void update(double interval);

	friend class Universe;
private:
	Region* activeRegion;
	BaseObject* object;
};

#endif	/* _CAMERA_H */

