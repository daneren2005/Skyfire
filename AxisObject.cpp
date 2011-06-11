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

#include "AxisObject.h"

AxisObject::AxisObject() : BaseObject()
{

}
AxisObject::AxisObject(float x, float y, float z) : BaseObject(x, y, z)
{

}
AxisObject::AxisObject(const AxisObject &orig)
{

}
AxisObject::~AxisObject()
{

}

void AxisObject::update(double interval)
{

}

void AxisObject::draw()
{
	float START = -100.0f;
	float END = 100.0f;
	float INCREMENT = 5.0f;

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDisable(GL_LIGHTING);

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
		for(float i = START; i < END; i += INCREMENT)
		{
			for(float j = START; j < END; j += INCREMENT)
			{
				glVertex3f(i, j, 0);
				glVertex3f(i + INCREMENT, j, 0);
				glVertex3f(i + INCREMENT, j + INCREMENT, 0);
				glVertex3f(i, j + INCREMENT, 0);
			}
		}
		for(float i = START; i < END; i += INCREMENT)
		{
			for(float j = START; j < END; j += INCREMENT)
			{
				glVertex3f(0.0f, i, j);
				glVertex3f(0.0f, i, j + INCREMENT);
				glVertex3f(0.0f, i + INCREMENT, j + INCREMENT);
				glVertex3f(0.0f, i + INCREMENT, j);
			}
		}
	glEnd();
}

void AxisObject::load()
{
	
}
