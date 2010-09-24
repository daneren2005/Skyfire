/* 
 * File:   Scene.h
 * Author: scott
 *
 * Created on July 14, 2010, 7:14 PM
 */

#ifndef _SCENE_H
#define	_SCENE_H

class Scene
{
public:
	Scene();
	Scene(const Scene& orig);
	virtual ~Scene();

	virtual void render() = 0;
private:

};

#endif	/* _SCENE_H */

