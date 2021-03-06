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

#ifndef _PARTICLE_H
#define	_PARTICLE_H

#include "Vector.h"

class Particle
{
public:
	Particle();
	Particle(Vector speed, Vector color, float fade = 0.0f);
	Particle(Vector position, Vector speed, Vector color, float fade = 0.0f);
	Particle(Vector position, Vector speed, Vector acceleration, Vector color, float fade = 0.0f);

	bool active;
	Vector position;
	Vector speed;
	Vector acceleration;
	Vector color;
	float life;
	float fade;
};

#endif	/* _PARTICLE_H */

