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
#include "List.h"

class ParticleEmitter : public BaseObject
{
public:
	ParticleEmitter();
	ParticleEmitter(const ParticleEmitter& orig);
	virtual ~ParticleEmitter();

	virtual void update(double interval);
	virtual void draw();
	virtual void load() = 0;
	void start();
	void stop();
protected:
	Array<Particle> particles;
	List<int> inactive;

	virtual void emitParticles(double interval) = 0;
	virtual void emitParticle(Vector speed, Vector color, float fade = 0.0f);
	virtual void emitParticle(Vector position, Vector speed, Vector color, float fade = 0.0f);
	virtual void emitParticle(Vector position, Vector speed, Vector acceleration, Vector color, float fade = 0.0f);
private:
	bool running;
};

#endif	/* _PARTICLEEMITTER_H */

