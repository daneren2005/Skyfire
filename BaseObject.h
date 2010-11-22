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

	virtual void update(double interval) = 0;
	virtual void transformObject();
	virtual void transformCamera();
	virtual void draw(bool forceDraw = false);

	virtual void load() = 0;

	bool operator==(const BaseObject& rhs);
	bool operator!=(const BaseObject& rhs);

	friend class Camera;
protected:
	Model model;
	Vector position;
	Vector angle;

	BaseObject* camera;
private:
	int objectID;
	static int objectIDCounter;
};

#endif	/* _BASEOBJECT_H */

