/* 
 * File:   ParticleSystem.h
 * Author: scott
 *
 * Created on January 13, 2011, 2:48 PM
 */

#ifndef _PARTICLESYSTEM_H
#define	_PARTICLESYSTEM_H

#include "Particle.h"
#include "Array.h"

class ParticleSystem
{
public:
	static const int PARTICLE_MAX = 100;

	ParticleSystem();
	ParticleSystem(const ParticleSystem& orig);
	virtual ~ParticleSystem();

	virtual void draw() = 0;

	void start();
	void stop();
private:
	Array<Particle> particles;
	bool running;
};

#endif	/* _PARTICLESYSTEM_H */

