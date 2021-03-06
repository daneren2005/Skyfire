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

#ifndef _MODEL_H
#define	_MODEL_H

#include "AxisAlignedBox.h"
#include "SharedPointer.h"
#include "Ray.h"
#include "Matrix4.h"

class Model
{
public:
	Model();
	Model(const Model& orig);
	virtual ~Model();

	virtual void computeBoundingBox() = 0;
	virtual AxisAlignedBox getBoundingBox() = 0;

	virtual void draw() = 0;
	virtual void drawFrame() = 0;
	virtual long numTriangles() = 0;
	
	virtual float getRayIntersection(const Ray& ray, const Matrix4& transform) = 0;
	virtual float getRayIntersection(Vector s, Vector r) = 0;
private:

};

typedef SharedPointer<Model> ModelPointer;

#endif	/* _MODEL_H */

