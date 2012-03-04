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

#ifndef _RENDERER_H
#define	_RENDERER_H

#include <GL/gl.h>
#include <GL/glu.h>

#include "Rectangle.h"
#include "Input.h"

class Renderer
{
public:
	Renderer();
	Renderer(const Renderer& orig);
	virtual ~Renderer();

	virtual void render() = 0;
	virtual void viewport2D();
	virtual void viewport3D();
	
	virtual Rectangle2 getScreenArea();
	virtual void setScreenArea(Rectangle2 area);
	
	virtual void setEventHandlers(Input* input);
protected:
	Rectangle2 screenArea;
	float aspectRatio;
	float nearPerspective;
	float farPerspective;
};

#endif	/* _SCENE_H */

