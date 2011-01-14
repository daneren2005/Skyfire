/* 
 * File:   ParticleSystem.cpp
 * Author: scott
 * 
 * Created on January 13, 2011, 2:48 PM
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

