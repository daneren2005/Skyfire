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