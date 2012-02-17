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
protected:
    BaseObject* object;
};

#endif	/* FIRSTPERSONCAMERA_H */

