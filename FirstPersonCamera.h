/* 
 * File:   FirstPersonCamera.h
 * Author: scott
 *
 * Created on July 15, 2011, 7:05 PM
 */

#ifndef FIRSTPERSONCAMERA_H
#define	FIRSTPERSONCAMERA_H

#include "Camera.h"

class FirstPersonCamera : public Camera
{
public:
	FirstPersonCamera();
	FirstPersonCamera(const FirstPersonCamera& orig);
	virtual ~FirstPersonCamera();
        
        void attachTo(BaseObject* object);
	void detach();
        
        virtual void moveBy(float x, float y, float z);
	virtual void moveBy(const Vector& amount);
	virtual void moveByDirection(float x, float y, float z);
	virtual void moveByDirection(const Vector& amount);
	virtual void moveTo(float x, float y, float z);
	virtual void moveTo(const Vector& amount);
	virtual void rotateBy(float x, float y, float z);
	virtual void rotateBy(const Vector& amount);
        
        virtual void draw();
protected:
    BaseObject* object;
};

#endif	/* FIRSTPERSONCAMERA_H */

