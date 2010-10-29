/*
 * File:   BaseObject.h
 * Author: scott
 *
 * Created on July 13, 2010, 8:20 PM
 */

#ifndef _BASEOBJECT_H
#define	_BASEOBJECT_H

#include "Mesh.h"
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
	virtual void transformCamera(const Vector& cameraPosition, const Vector& cameraAngle);
	virtual void draw();

	virtual void load();

	friend class Camera;
protected:
	Mesh mesh;
	Vector position;
	Vector angle;

	Camera* camera;
private:
	static int objectIDCounter;
};

#endif	/* _BASEOBJECT_H */

