/*
 * File:   BaseObject.h
 * Author: scott
 *
 * Created on July 13, 2010, 8:20 PM
 */

#ifndef _BASEOBJECT_H
#define	_BASEOBJECT_H

#include "Mesh.h"
#include "Vector.h"

class BaseObject
{
public:
	BaseObject();
	BaseObject(float x, float y, float z);
	BaseObject(const BaseObject& orig);
	virtual ~BaseObject();

	virtual void moveByReference(float x, float y, float z);
	virtual void moveByReference(const Vector& amount);
	virtual void moveByAbsolute(float x, float y, float z);
	virtual void moveByAbsolute(const Vector& amount);
	virtual void moveTo(float x, float y, float z);
	virtual void moveTo(const Vector& amount);
	virtual void rotateByReference(float x, float y, float z);
	virtual void rotateByReference(const Vector& amount);
	virtual void rotateByAbsolute(float x, float y, float z);
	virtual void rotateByAbsolute(const Vector& amount);

	virtual void update(double interval) = 0;
	virtual void draw(Vector cameraPosition, Vector cameraAngle);

	virtual void load();
protected:
	Mesh* shape;
	Vector position;
	Vector angle;
private:
	static int objectIDCounter;
};

#endif	/* _BASEOBJECT_H */
