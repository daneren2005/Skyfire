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

#include "Material.h"

Material::Material()
{
	for(int i = 0; i < 3; i++)
	{
		this->ambient[i] = 0.0f;
		this->diffuse[i] = 0.0f;
		this->specular[i] = 0.0f;
		this->transmissionFilter[i] = 1.0f;
	}

	this->shininess = 0.0f;
	this->transparency = 1.0f;
	this->refraction = 1.0f;

	this->textureMap = 0x0;
	this->bumpMap = 0x0;
	this->diffuseMap = 0x0;
}

Material::Material(const Material& orig)
{
	for(int i = 0; i < 3; i++)
	{
		this->ambient[i] = orig.ambient[i];
		this->diffuse[i] = orig.diffuse[i];
		this->specular[i] = orig.specular[i];
		this->transmissionFilter[i] = orig.transmissionFilter[i];
	}

	this->shininess = orig.shininess;
	this->transparency = orig.transparency;
	this->refraction = orig.refraction;

	this->textureMap = orig.textureMap;
	this->bumpMap = orig.bumpMap;
	this->diffuseMap = orig.diffuseMap;
}

Material::~Material()
{
}

