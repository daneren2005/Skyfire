/* 
 * File:   Particle.h
 * Author: scott
 *
 * Created on January 13, 2011, 3:38 PM
 */

#ifndef _PARTICLE_H
#define	_PARTICLE_H

#include "Vector.h"

struct Particle
{
	Vector position;
	Vector speed;
	Vector color;
	float life;
	float totalLife;
	float fade;
	float fadeSpeed;
};

#endif	/* _PARTICLE_H */

