/*
 * File:   MeshPart.h
 * Author: scott
 *
 * Created on September 29, 2010, 4:04 PM
 */

#ifndef _MeshPart_H
#define	_MeshPart_H

#include "Array.h"
#include "Triangle.h"
#include "Bitmap.h"
#include "Vector.h"

struct Vertex
{
	Vector position;
	Vector normal;
	Vector texture;
};

struct Material
{
	float ambient[3];
	float diffuse[3];
	float specular[3];
	float shininess;
	float transparency; // 1 = normal, 0 = transparent
	float refraction; // 1 = light doesnt bend, > 1 = light bends
	float transmissionFiler[3]; // light filter for rgb, 1 = allows, 0 = disallows
	Bitmap* diffuseMap;
	Bitmap* bumpMap;
};

class MeshPart : public Array<Vertex>
{
public:
	MeshPart();
	MeshPart(unsigned long size, bool wireFrame = false);
	MeshPart(const MeshPart& orig);
	virtual ~MeshPart();

	void draw();

	Material material;
	void setWireFrame(bool option);
private:
	bool wireFrame;
};

#endif	/* _MeshPart_H */

