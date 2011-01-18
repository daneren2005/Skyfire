#include "Particle.h"

Particle::Particle()
{
	this->active = true;
	this->position = Vector();
	this->speed = Vector();
	this->acceleration = Vector();
	this->color = Vector();
	this->life = 1.0f;
	this->fade = 0.0f;
}

Particle::Particle(Vector speed, Vector color, float fade)
{
	this->active = true;
	this->position = Vector();
	this->speed = speed;
	this->acceleration = Vector();
	this->color = color;
	this->life = 1.0f;
	this->fade = fade;
}

Particle::Particle(Vector position, Vector speed, Vector color, float fade)
{
	this->active = true;
	this->position = position;
	this->speed = speed;
	this->acceleration = Vector();
	this->color = color;
	this->life = 1.0f;
	this->fade = fade;
}

Particle::Particle(Vector position, Vector speed, Vector acceleration, Vector color, float fade)
{
	this->active = true;
	this->position = position;
	this->speed = speed;
	this->acceleration = acceleration;
	this->color = color;
	this->life = 1.0f;
	this->fade = fade;
}