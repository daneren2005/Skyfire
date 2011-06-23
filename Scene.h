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

#ifndef _SCENE_H
#define	_SCENE_H

#include "Rectangle.h"

class Scene
{
public:
	Scene();
	Scene(const Scene& orig);
	virtual ~Scene();

	void render();
	virtual void draw() = 0;
protected:
	Rectangle2 screenArea;
	float aspectRatio;
	float nearPerspective;
	float farPerspective;
};

#endif	/* _SCENE_H */

