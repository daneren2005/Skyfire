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

