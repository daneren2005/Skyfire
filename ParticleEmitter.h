/* 
 * File:   ParticleEmitter.h
 * Author: scott
 *
 * Created on January 13, 2011, 3:06 PM
 */

#ifndef _PARTICLEEMITTER_H
#define	_PARTICLEEMITTER_H

#include "BaseObject.h"
#include "Particle.h"
#include "Array.h"

class ParticleEmitter : public BaseObject
{
public:
	ParticleEmitter();
	ParticleEmitter(const ParticleEmitter& orig);
	virtual ~ParticleEmitter();

	virtual void update(double interval) = 0;
	virtual void draw() = 0;
	virtual void load() = 0;
	void start();
	void stop();
protected:
	Array<Particle> particles;

	virtual void emitParticles() = 0;
private:
	bool running;
};

#endif	/* _PARTICLEEMITTER_H */

