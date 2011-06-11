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

