/* 
 * File:   Particle.h
 * Author: scott
 *
 * Created on January 13, 2011, 3:38 PM
 */

#ifndef _PARTICLE_H
#define	_PARTICLE_H

#include "Vector.h"

class Particle
{
public:
	Particle();
	Particle(Vector speed, Vector color, float fade = 0.0f);
	Particle(Vector position, Vector speed, Vector color, float fade = 0.0f);
	Particle(Vector position, Vector speed, Vector acceleration, Vector color, float fade = 0.0f);

	bool active;
	Vector position;
	Vector speed;
	Vector acceleration;
	Vector color;
	float life;
	float fade;
};

#endif	/* _PARTICLE_H */

