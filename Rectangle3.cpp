/* 
 * File:   Rectangle3.cpp
 * Author: scott
 * 
 * Created on February 15, 2011, 2:58 PM
 */

#include "Rectangle3.h"
#include <GL/gl.h>

Rectangle3::Rectangle3()
{
	this->lx = 0.0f;
	this->ly = 0.0f;
	this->lz = 0.0f;
	this->ux = 0.0f;
	this->uy = 0.0f;
	this->uz = 0.0f;
}

Rectangle3::Rectangle3(float lx, float ly, float lz, float ux, float uy, float uz)
{
	this->lx = lx;
	this->ly = ly;
	this->lz = lz;
	this->ux = ux;
	this->uy = uy;
	this->uz = uz;
}

Rectangle3::Rectangle3(const Rectangle3& orig)
{
}

Rectangle3::~Rectangle3()
{
}

void Rectangle3::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Draw a red box
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
		glVertex3f(lx, ly, lz);
		glVertex3f(lx, ly, uz);

		glVertex3f(lx, ly, lz);
		glVertex3f(lx, uy, lz);

		glVertex3f(lx, ly, lz);
		glVertex3f(ux, ly, lz);

		glVertex3f(lx, ly, uz);
		glVertex3f(lx, uy, uz);

		glVertex3f(lx, ly, uz);
		glVertex3f(ux, ly, uz);

		glVertex3f(lx, uy, lz);
		glVertex3f(ux, uy, lz);

		glVertex3f(lx, uy, lz);
		glVertex3f(lx, uy, uz);

		glVertex3f(ux, ly, lz);
		glVertex3f(ux, uy, lz);

		glVertex3f(ux, ly, lz);
		glVertex3f(ux, ly, uz);

		glVertex3f(lx, uy, uz);
		glVertex3f(ux, uy, uz);

		glVertex3f(ux, ly, uz);
		glVertex3f(ux, uy, uz);

		glVertex3f(ux, uy, lz);
		glVertex3f(ux, uy, uz);
	glEnd();
}

bool Rectangle3::pointIn(float x, float y, float z)
{
	if(x > lx && x < ux && y > ly && y < uy && z > lz && z < uz)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Rectangle3::collision(Rectangle3 rhs)
{
	if(this->pointIn(rhs.lx, rhs.ly, rhs.lz))
	{
		return true;
	}
	else
	{
		return false;
	}
}

