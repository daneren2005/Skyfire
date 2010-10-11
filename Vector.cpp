/*
 * File:   Vector.cpp
 * Author: scott
 *
 * Created on July 13, 2010, 8:22 PM
 */

#include "Vector.h"

Vector::Vector()
{
	this->pos[0] = 0;
	this->pos[1] = 0;
	this->pos[2] = 0;

	pthread_mutex_init(&this->lock, NULL);
}
Vector::Vector(float x, float y)
{
	this->pos[0] = x;
	this->pos[1] = y;
	this->pos[2] = 0.0f;

	pthread_mutex_init(&this->lock, NULL);
}
Vector::Vector(float x, float y, float z)
{
	this->pos[0] = x;
	this->pos[1] = y;
	this->pos[2] = z;

	pthread_mutex_init(&this->lock, NULL);
}

Vector::Vector(const Vector& orig)
{
	this->pos[0] = orig.pos[0];
	this->pos[1] = orig.pos[1];
	this->pos[2] = orig.pos[2];

	pthread_mutex_init(&this->lock, NULL);
}

Vector::~Vector()
{
	// pthread_mutex_destroy(&this->lock);
}

float Vector::x() const
{
	// pthread_mutex_lock(&this->lock);
	float value = pos[0];
	// pthread_mutex_unlock(&this->lock);
	return value;
}
float Vector::y() const
{
	// pthread_mutex_lock(&this->lock);
	float value = pos[1];
	// pthread_mutex_unlock(&this->lock);
	return value;
}
float Vector::z() const
{
	// pthread_mutex_lock(&this->lock);
	float value = pos[2];
	// pthread_mutex_unlock(&this->lock);
	return value;
}

// Vector::operator Overloading
float& Vector::operator[](unsigned col)
{
	// pthread_mutex_lock(&this->lock);
	if(col >= 0 && col < 3)
	{
		return pos[col];
	}
	else
	{
		float value = 0.0f;
		return value;
	}
	// pthread_mutex_unlock(&this->lock);
}

Vector Vector::operator+(const Vector& rhs)
{
	// pthread_mutex_lock(&this->lock);
	Vector vec(this->x() + this->x(), this->y() + rhs.y(), this->z() + rhs.z());
	// pthread_mutex_unlock(&this->lock);
	return vec;
}
Vector Vector::operator-(const Vector& rhs)
{
	// pthread_mutex_lock(&this->lock);
	Vector vec(this->x() - rhs.x(), this->y() - rhs.y(), this->z() - rhs.z());
	// pthread_mutex_unlock(&this->lock);
	return vec;
}
Vector Vector::operator*(const Vector& rhs)
{
	// pthread_mutex_lock(&this->lock);
	Vector vec(this->x() * rhs.x(), this->y() * rhs.y(), this->z() * rhs.z());
	// pthread_mutex_unlock(&this->lock);
	return vec;
}
Vector Vector::operator%(const float amount)
{
	// pthread_mutex_lock(&this->lock);
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
	// pthread_mutex_unlock(&this->lock);
	return vec;
}

bool Vector::operator==(const Vector& rhs)
{
	// pthread_mutex_lock(&this->lock);
	bool value;
	if(this->x() != rhs.x())
		value = false;
	else if(this->y() != rhs.y())
		value = false;
	else if(this->z() != rhs.z())
		value = false;
	else
		value = true;
	// pthread_mutex_unlock(&this->lock);
	return value;
}
bool Vector::operator!=(const Vector& rhs)
{
	// pthread_mutex_lock(&this->lock);
	bool value;
	if(this->x() != rhs.x())
		value = true;
	else if(this->y() != rhs.y())
		value = true;
	else if(this->z() != rhs.z())
		value = true;
	else
		value = false;
	// pthread_mutex_unlock(&this->lock);
	return value;
}

