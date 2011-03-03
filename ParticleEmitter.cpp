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

void ParticleEmitter::update(double interval)
{
	if(running)
		this->emitParticles(interval);

	Particle* ptr = this->particles.getPointer();
	for(int i = 0; i < this->particles.size(); i++)
	{
		ptr[i].position = ptr[i].position + (ptr[i].speed * interval);
		ptr[i].speed = ptr[i].speed + (ptr[i].acceleration * (interval * interval));
		ptr[i].life -= interval * ptr[i].fade;
		if(ptr[i].life <= 0 && ptr[i].active)
		{
			ptr[i].active = false;
			inactive.pushBack(i);
		}
	}
}

void ParticleEmitter::draw()
{
	glEnable (GL_BLEND); glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Particle* ptr = this->particles.getPointer();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
	for(int i = 0; i < this->particles.size(); i++)
	{
		if(ptr[i].life >= 0)
		{
			glColor4f(1.0f, 0.1f, 0.0f, ptr[i].life);
			glVertex3f(ptr[i].position[0] + 0.1f, ptr[i].position[1] + 0.1f, ptr[i].position[2]);
			glVertex3f(ptr[i].position[0] - 0.1f, ptr[i].position[1] + 0.1f, ptr[i].position[2]);
			glVertex3f(ptr[i].position[0] + 0.1f, ptr[i].position[1] - 0.1f, ptr[i].position[2]);
			glVertex3f(ptr[i].position[0] - 0.1f, ptr[i].position[1] + 0.1f, ptr[i].position[2]);
			glVertex3f(ptr[i].position[0] + 0.1f, ptr[i].position[1] - 0.1f, ptr[i].position[2]);
			glVertex3f(ptr[i].position[0] - 0.1f, ptr[i].position[1] - 0.1f, ptr[i].position[2]);
		}
	}
	glEnd();
}

void ParticleEmitter::start()
{
	this->running = true;
}
void ParticleEmitter::stop()
{
	this->running = false;
}

void ParticleEmitter::emitParticle(Vector speed, Vector color, float fade)
{
	if(inactive.size() <= 0)
	{
		this->particles.insert(Particle(speed, color, fade));
	}
	else
	{
		this->particles[inactive.popFront()] = Particle(speed, color, fade);
	}
}
void ParticleEmitter::emitParticle(Vector position, Vector speed, Vector color, float fade)
{
	if(inactive.size() <= 0)
	{
		this->particles.insert(Particle(position, speed, color, fade));
	}
	else
	{
		this->particles[inactive.popFront()] = Particle(position, speed, color, fade);
	}
}
void ParticleEmitter::emitParticle(Vector position, Vector speed, Vector acceleration, Vector color, float fade)
{
	if(inactive.size() <= 0)
	{
		this->particles.insert(Particle(position, speed, acceleration, color, fade));
	}
	else
	{
		this->particles[inactive.popFront()] = Particle(position, speed, acceleration, color, fade);
	}
}

