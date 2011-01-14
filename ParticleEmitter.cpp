/* 
 * File:   ParticleEmitter.cpp
 * Author: scott
 * 
 * Created on January 13, 2011, 3:06 PM
 */

#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter()
{
	this->running = false;
}

ParticleEmitter::ParticleEmitter(const ParticleEmitter& orig)
{
	this->running = orig.running;
}

ParticleEmitter::~ParticleEmitter()
{

}

void ParticleEmitter::start()
{
	this->running = true;
}
void ParticleEmitter::stop()
{
	this->running = false;
}

