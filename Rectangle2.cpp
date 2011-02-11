#include "Rectangle2.h"

Rectangle2::Rectangle2()
{
	this->lx = 0;
	this->ly = 0;
	this->ux = 0;
	this->uy = 0;
}
Rectangle2::Rectangle2(int lx, int ly, int ux, int uy)
{
	this->lx = lx;
	this->ly = ly;
	this->ux = ux;
	this->uy = uy;
}

Rectangle2::~Rectangle2()
{
}
