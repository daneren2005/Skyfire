/*
 * File:   Vector.cpp
 * Author: scott
 *
 * Created on July 13, 2010, 8:22 PM
 */

#include "Vector.h"
#include "Exceptions.h"

Vector::Vector()
{
	this->pos[0] = 0.0f;
	this->pos[1] = 0.0f;
	this->pos[2] = 0.0f;
}
Vector::Vector(float x, float y)
{
	this->pos[0] = x;
	this->pos[1] = y;
	this->pos[2] = 0.0f;
}
Vector::Vector(float x, float y, float z)
{
	this->pos[0] = x;
	this->pos[1] = y;
	this->pos[2] = z;
}

Vector::Vector(const Vector& orig)
{
	this->pos[0] = orig.pos[0];
	this->pos[1] = orig.pos[1];
	this->pos[2] = orig.pos[2];
}

Vector::~Vector()
{
}

float Vector::x() const
{
	return pos[0];
}
float Vector::y() const
{
	return pos[1];
}
float Vector::z() const
{
	return pos[2];
}

// Vector::operator Overloading
float& Vector::operator[](unsigned col)
{
	if(col >= 0 && col < 3)
	{
		return pos[col];
	}
	else
	{
		throw OutOfRange();
	}
}

const float& Vector::operator[](unsigned col) const
{
	if(col >= 0 && col < 3)
	{
		return pos[col];
	}
	else
	{
		throw OutOfRange();
	}
}

Vector Vector::operator+(const Vector& rhs)
{
	Vector vec(this->x() + rhs.x(), this->y() + rhs.y(), this->z() + rhs.z());
	return vec;
}
Vector Vector::operator+(const Vector& rhs) const
{
	Vector vec(this->x() + rhs.x(), this->y() + rhs.y(), this->z() + rhs.z());
	return vec;
}
Vector& Vector::operator+=(const Vector& rhs)
{
	this->pos[0] += rhs[0];
	this->pos[1] += rhs[1];
	this->pos[2] += rhs[2];

	return *this;
}

Vector Vector::operator-(const Vector& rhs)
{
	Vector vec(this->x() - rhs.x(), this->y() - rhs.y(), this->z() - rhs.z());
	return vec;
}
Vector Vector::operator-(const Vector& rhs) const
{
	Vector vec(this->x() - rhs.x(), this->y() - rhs.y(), this->z() - rhs.z());
	return vec;
}
Vector& Vector::operator-=(const Vector& rhs)
{
	this->pos[0] -= rhs[0];
	this->pos[1] -= rhs[1];
	this->pos[2] -= rhs[2];

	return *this;
}
Vector Vector::operator*(const Vector& rhs)
{
	Vector vec(this->pos[1] * rhs[2] - this->pos[2] * rhs[1], this->pos[2] * rhs[0] - this->pos[0] * rhs[2], this->pos[0] * rhs[1] - this->pos[1] * rhs[0]);
	return vec;
}
Vector Vector::operator*(const Vector& rhs) const
{
	Vector vec(this->pos[1] * rhs[2] - this->pos[2] * rhs[1], this->pos[2] * rhs[0] - this->pos[0] * rhs[2], this->pos[0] * rhs[1] - this->pos[1] * rhs[0]);
	return vec;
}
Vector& Vector::operator*=(const Vector& rhs)
{
	*this = *this * rhs;
	return *this;
}
Vector Vector::operator*(const float& rhs)
{
	return Vector(pos[0] * rhs, pos[1] * rhs, pos[2] * rhs);
}
Vector Vector::operator*(const float& rhs) const
{
	return Vector(pos[0] * rhs, pos[1] * rhs, pos[2] * rhs);
}
Vector& Vector::operator*=(const float& rhs)
{
	this->pos[0] *= rhs;
	this->pos[1] *= rhs;
	this->pos[2] *= rhs;
	return *this;
}

Vector Vector::operator%(const float& amount)
{
	int x = (int)(this->x() / amount);
	float x_val = this->x() - x * amount;
	if(x_val < 0.0f)
		x_val = amount + x_val;

	int y = (int)(this->y() / amount);
	float y_val = this->y() - y * amount;
	if(y_val < 0.0f)
		y_val = amount + y_val;

	int z = (int)(this->z() / amount);
	float z_val = this->z() - z * amount;
	if(z_val < 0.0f)
		z_val = amount + z_val;

	Vector vec(x_val, y_val, z_val);
	return vec;
}

Vector Vector::operator%(const float& amount) const
{
	int x = (int)(this->x() / amount);
	float x_val = this->x() - x * amount;
	if(x_val < 0.0f)
		x_val = amount + x_val;

	int y = (int)(this->y() / amount);
	float y_val = this->y() - y * amount;
	if(y_val < 0.0f)
		y_val = amount + y_val;

	int z = (int)(this->z() / amount);
	float z_val = this->z() - z * amount;
	if(z_val < 0.0f)
		z_val = amount + z_val;

	Vector vec(x_val, y_val, z_val);
	return vec;
}

Vector& Vector::operator%=(const float& amount)
{
	int x = (int)(this->pos[0] / amount);
	this->pos[0] = this->pos[0] - x * amount;
	if(this->pos[0] < 0.0f)
		this->pos[0] += amount;

	int y = (int)(this->pos[1] / amount);
	this->pos[1] = this->pos[1] - y * amount;
	if(this->pos[1] < 0.0f)
		this->pos[1] += amount;

	int z = (int)(this->pos[2] / amount);
	this->pos[2] = this->pos[2] - z * amount;
	if(this->pos[2] < 0.0f)
		this->pos[2] += amount;

	return *this;
}

bool Vector::operator==(const Vector& rhs)
{
	if(this->x() != rhs.x())
		return false;
	else if(this->y() != rhs.y())
		return false;
	else if(this->z() != rhs.z())
		return false;

	return true;
}
bool Vector::operator!=(const Vector& rhs)
{
	if(this->x() != rhs.x())
		return true;
	else if(this->y() != rhs.y())
		return true;
	else if(this->z() != rhs.z())
		return true;

	return false;
}

Vector Vector::operator!()
{
	return Vector(-this->x(), -this->y(), -this->z());
}

Vector Vector::projection(const Vector& b) const
{
	float dot = pos[0] * b.pos[0] + pos[1] * b.pos[1] + pos[2] * b.pos[2];
	float a = pos[0] * pos[0] + pos[1] * pos[1] + pos[2] * pos[2];

	return *this * (dot / a);
}

float* Vector::getPointer()
{
	return &(pos[0]);
}
