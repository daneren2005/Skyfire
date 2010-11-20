#include "AxisObject.h"

AxisObject::AxisObject() : BaseObject(0.0f, 0.0f, 0.0f)
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

void AxisObject::draw(bool forceDraw)
{
	float START = -100.0f;
	float END = 100.0f;
	float INCREMENT = 5.0f;

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
