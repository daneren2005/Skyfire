/*
 * File:   Vector.h
 * Author: scott
 *
 * Created on July 13, 2010, 8:22 PM
 */

#ifndef _VECTOR_H
#define	_VECTOR_H

#ifdef WIN32
    #include <windows.h>
#endif

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

	Vector operator+(const Vector& rhs);
	Vector operator-(const Vector& rhs);
	Vector operator*(const Vector& rhs);
	Vector operator%(const float amount);

	bool operator==(const Vector& rhs);
	bool operator!=(const Vector& rhs);

	Vector operator!();
private:
	float pos[3];
	pthread_mutex_t lock;
};

// Opengl functions
static void glTranslatev(Vector vector)
{
	glTranslatef(vector[0], vector[1], vector[2]);
}
static void glRotatev(Vector vector)
{
	// Get max number
	float max;
	if(vector[0] > vector[1])
		max = vector[0];
	else
		max = vector[1];
	if(vector[2] > max)
		max = vector[2];

	glRotatef(max, vector[0] / max, vector[1] / max, vector[2] / max);
}

#endif	/* _VECTOR_H */

