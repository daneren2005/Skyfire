#include "Rectangle.h"

Rectangle::Rectangle()
{
	this->lx = 0;
	this->ly = 0;
	this->ux = 0;
	this->uy = 0;
}
Rectangle::Rectangle(int lx, int ly, int ux, int uy)
{
	this->lx = lx;
	this->ly = ly;
	this->ux = ux;
	this->uy = uy;
}

Rectangle::~Rectangle()
{
}
