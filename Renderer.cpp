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

#include "Renderer.h"
#include "BaseObject.h"
#include <GL/glu.h>

Renderer::Renderer()
{
	this->screenArea = Rectangle2(0, 0, 1280, 720);
	this->aspectRatio = (float)(screenArea.ux - screenArea.lx) / (float)(screenArea.uy - screenArea.ly);
	this->nearPerspective = 0.1f;
	this->farPerspective = 100.0f;
}

Renderer::Renderer(const Renderer& orig)
{
	this->screenArea = orig.screenArea;
	this->aspectRatio = orig.aspectRatio;
	this->nearPerspective = orig.nearPerspective;
	this->farPerspective = orig.farPerspective;
}

Renderer::~Renderer()
{
}

void Renderer::viewport()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(this->screenArea.lx, this->screenArea.ly, this->screenArea.ux, this->screenArea.uy);
	gluPerspective(45.0f, this->aspectRatio, this->nearPerspective, this->farPerspective);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

Rectangle2 Renderer::getScreenArea()
{
	return screenArea;
}
void Renderer::setScreenArea(Rectangle2 area)
{
	screenArea = area;
}

void Renderer::setEventHandlers(Input* input)
{
	
}
