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

#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
	this->running = false;
	this->particles = Array<Particle>(ParticleSystem::PARTICLE_MAX);
}

ParticleSystem::ParticleSystem(const ParticleSystem& orig)
{
	this->running = orig.running;
	this->particles = orig.particles;
}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::start()
{
	this->running = true;
}
void ParticleSystem::stop()
{
	this->running = false;
}

