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

	virtual void moveBy(float x, float y, float z);
	virtual void moveBy(const Vector& amount);
	virtual void moveByDirection(float x, float y, float z);
	virtual void moveByDirection(const Vector& amount);
	virtual void moveTo(float x, float y, float z);
	virtual void moveTo(const Vector& amount);
	virtual void rotateBy(float x, float y, float z);
	virtual void rotateBy(const Vector& amount);

	void attachTo(BaseObject* object);
	void detach();
	void setActiveRegion(Region* region);
	Region* getActiveRegion();

	virtual void render();

	virtual void draw();
	virtual void update(double interval);
	virtual void load();

	friend class Universe;
private:
	Region* activeRegion;
	BaseObject* object;
};

#endif	/* _CAMERA_H */

