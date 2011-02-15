/* 
 * File:   Scene.h
 * Author: scott
 *
 * Created on July 14, 2010, 7:14 PM
 */

#ifndef _SCENE_H
#define	_SCENE_H

#include "Rectangle2.h"

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

