/* 
 * File:   Scene.cpp
 * Author: scott
 * 
 * Created on July 14, 2010, 7:14 PM
 */

#include "Scene.h"
#include "BaseObject.h"
#include <GL/glu.h>

Scene::Scene()
{
	this->screenArea = Rectangle2(0, 0, 1280, 720);
	this->aspectRatio = (float)(screenArea.ux - screenArea.lx) / (float)(screenArea.uy - screenArea.ly);
	this->nearPerspective = 0.1f;
	this->farPerspective = 100.0f;
}

Scene::Scene(const Scene& orig)
{
	this->screenArea = orig.screenArea;
	this->aspectRatio = orig.aspectRatio;
	this->nearPerspective = orig.nearPerspective;
	this->farPerspective = orig.farPerspective;
}

Scene::~Scene()
{
}

void Scene::render()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(this->screenArea.lx, this->screenArea.ly, this->screenArea.ux, this->screenArea.uy);
	gluPerspective(45.0f, this->aspectRatio, this->nearPerspective, this->farPerspective);
	glMatrixMode(GL_MODELVIEW);

	this->draw();
}
