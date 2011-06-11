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

#include "Scene.h"
#include "BaseObject.h"
#include <GL/glu.h>

Scene::Scene()
{
	this->screenArea = Rectangle(0, 0, 1280, 720);
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
