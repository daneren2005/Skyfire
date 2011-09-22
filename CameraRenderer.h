/* 
 * File:   CameraRenderer.h
 * Author: scott
 *
 * Created on July 21, 2011, 7:45 PM
 */

#ifndef CAMERARENDERER_H
#define	CAMERARENDERER_H

#include "Renderer.h"

#include "Camera.h"

class CameraRenderer : public Renderer
{
public:
	CameraRenderer();
	CameraRenderer(const CameraRenderer& orig);
	virtual ~CameraRenderer();
	
	virtual void render();
	
	void setCamera(Camera* camera);
	Camera* getCamera();
private:
	Camera* camera;
};

#endif	/* CAMERARENDERER_H */

