/*
 * File:   BaseObject.h
 * Author: scott
 *
 * Created on July 13, 2010, 8:20 PM
 */

#ifndef _BASEOBJECT_H
#define	_BASEOBJECT_H

#include "Model.h"
#include "Matrix4.h"
#include "Vector.h"

class Camera;

class BaseObject
{
public:
	BaseObject();
	BaseObject(float x, float y, float z);
	BaseObject(const BaseObject& orig);
	virtual ~BaseObject();

	virtual void moveBy(float x, float y, float z);
	virtual void moveBy(const Vector& amount);
	virtual void moveByDirection(float x, float y, float z);
	virtual void moveByDirection(const Vector& amount);
	virtual void moveTo(float x, float y, float z);
	virtual void moveTo(const Vector& amount);
	virtual void rotateBy(float x, float y, float z);
	virtual void rotateBy(const Vector& amount);

	// Called regularly to update based on how much time has passed since last called
	virtual void update(double interval) = 0;
	// Move object and rotate it around its own axis
	virtual void transformObject();
	// Move object and rotate it around cameras axis
	virtual void transformCamera();
	// Called when trying to draw the object on the screen
	virtual void draw() = 0;
	// Called when intializing an object (loading model data, etc)
	virtual void load() = 0;

	bool operator==(const BaseObject& rhs);
	bool operator!=(const BaseObject& rhs);

	friend class Camera;
protected:
	Vector position;
	Vector directionForward;
	Vector directionUp;

	BaseObject* camera;
private:
	int objectID;
	static int objectIDCounter;
};

#endif	/* _BASEOBJECT_H */

