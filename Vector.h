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

#ifndef _VECTOR_H
#define	_VECTOR_H

#ifdef WIN32
    #include <windows.h>
#endif

#include "Console.h"
#include <GL/gl.h>
#include <pthread.h>

class Vector {
public:
	Vector();
	Vector(float x, float y);
	Vector(float x, float y, float z);
	Vector(const Vector& orig);
	~Vector();

	// Get positions
	float x() const;
	float y() const;
	float z() const;

	// Operator Overloading
	float& operator[](unsigned col);
	const float& operator[](unsigned col) const;

	Vector operator+(const Vector& rhs);
	Vector operator+(const Vector& rhs) const;
	Vector& operator+=(const Vector& rhs);
	Vector operator-(const Vector& rhs);
	Vector operator-(const Vector& rhs) const;
	Vector& operator-=(const Vector& rhs);
	Vector operator*(const Vector& rhs);
	Vector operator*(const Vector& rhs) const;
	Vector& operator*=(const Vector& rhs);
	Vector operator*(const float& rhs);
	Vector operator*(const float& rhs) const;
	Vector& operator*=(const float& rhs);
	Vector operator/(const float& rhs);
	Vector operator/(const float& rhs) const;
	Vector& operator/=(const float& rhs);
	Vector operator%(const float& amount);
	Vector operator%(const float& amount) const;
	Vector& operator%=(const float& amount);

	bool operator==(const Vector& rhs);
	bool operator!=(const Vector& rhs);

	Vector operator!();
	Vector projection(const Vector& b) const;
	float magnitude() const;

	float* getPointer();
private:
	float pos[3];
};

#endif	/* _VECTOR_H */

