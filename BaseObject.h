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

#ifndef _BASEOBJECT_H
#define	_BASEOBJECT_H

#include "Mesh.h"
#include "Matrix4.h"
#include "Vector.h"
#include "DataFile.h"

class Region;
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

	virtual int getObjectId();
	virtual Vector getPosition();
	virtual Vector getAngle();
	virtual Camera* getAttachedCamera();
	virtual void setAttachedCamera(Camera* camera);
	virtual Region* getParentRegion();
	virtual void setParentRegion(Region* region);
	virtual void setModel(ModelPointer model);
	virtual ModelPointer getModel();

	// Called regularly to update based on how much time has passed since last called
	virtual void update(double interval) = 0;
	// Move object and rotate it around its own axis
	virtual void transform();
	virtual Matrix4 getTransform();
	// Move object and rotate it around cameras axis
	virtual void transformInverse();
	virtual Matrix4 getTransformInverse();
	// Called when trying to draw the object on the screen
	virtual void draw();
	virtual void drawEvent();
	// Called when initializing an object (loading model data, etc)
	virtual void load();
	// Called when initializing an object based off of a DataFile::Object
	virtual void load(DataFile::Object* unit, DataFile::Object* instance);
	// Called to get a generic Bounding Box around a object
	virtual AxisAlignedBox getBoundingBox();

	bool operator==(const BaseObject& rhs);
	bool operator!=(const BaseObject& rhs);
protected:
	Vector position;
	Vector directionForward;
	Vector directionUp;
	Vector scale;
	ModelPointer model;

	Region* parentRegion;
	Camera* attachedCamera;
private:
	int objectID;
	static int objectIDCounter;
};

#endif	/* _BASEOBJECT_H */

