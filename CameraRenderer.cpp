/* 
 * File:   CameraRenderer.cpp
 * Author: scott
 * 
 * Created on July 21, 2011, 7:45 PM
 */

#include "CameraRenderer.h"
#include <GL/glu.h>

CameraRenderer::CameraRenderer()
{
	this->camera = 0x0;
}

CameraRenderer::CameraRenderer(const CameraRenderer& orig)
{
	this->camera = orig.camera;
}

CameraRenderer::~CameraRenderer()
{
}

void CameraRenderer::setCamera(Camera* camera)
{
	this->camera = camera;
}
Camera* CameraRenderer::getCamera()
{
	return this->camera;
}

void CameraRenderer::render()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(this->screenArea.lx, this->screenArea.ly, this->screenArea.ux, this->screenArea.uy);
	gluPerspective(45.0f, this->aspectRatio, this->nearPerspective, this->farPerspective);
	glMatrixMode(GL_MODELVIEW);
	
	this->camera->draw();
}

void CameraRenderer::draw()
{
	
}
