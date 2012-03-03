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
#ifndef _CAMERA_H
#define	_CAMERA_H

#include "Renderer.h"
#include "Region.h"

class Universe;

class Camera : public Renderer
{
public:
	Camera();
	Camera(const Camera& orig);
	virtual ~Camera();
	
	virtual void render();
	virtual void renderHUD();

	virtual void setActiveRegion(Region* region);
	virtual Region* getActiveRegion();
	
	// Change position within region
	virtual void moveBy(float x, float y, float z);
	virtual void moveBy(const Vector& amount);
	virtual void moveByDirection(float x, float y, float z);
	virtual void moveByDirection(const Vector& amount);
	virtual void moveTo(float x, float y, float z);
	virtual void moveTo(const Vector& amount);
	virtual void rotateBy(float x, float y, float z);
	virtual void rotateBy(const Vector& amount);
	virtual void rotateTo(float x, float y, float z);
	virtual void rotateTo(const Vector& amount);
	virtual void transform();
	virtual Matrix4 getTransform();
	
	// Get details of viewed region
	virtual Vector projectMouseBack(int x, int y);
	virtual Ray projectMouseRay(int x, int y);
	virtual BaseObject* getObjectAt(int x, int y);
	virtual Array<BaseObject*> getOBjectsIn(int x, int y, int width, int height);

	friend class Universe;
protected:
	Region* activeRegion;
	Vector position;
	Vector direction;
};

#endif	/* _CAMERA_H */

