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

#include "ResourceManager.h"

#include <stdio.h>
#include <string.h>
#include "Timer.h"
#include "jpeglib.h"

ResourceManager resourceManager = ResourceManager();

ResourceManager::ResourceManager()
{
}

ResourceManager::ResourceManager(const ResourceManager& orig)
{
}

ResourceManager::~ResourceManager()
{
}

void ResourceManager::loadModel(char* filename, char* name)
{
	this->loadModel(String(filename), String(name));
}
void ResourceManager::loadModel(char* filename, String name)
{
	this->loadModel(String(filename), name);
}
void ResourceManager::loadModel(String filename, char* name)
{
	this->loadModel(filename, String(name));
}
void ResourceManager::loadModel(String filename, String name)
{
	File file(filename);

	if(file.getFileType() == "obj")
	{
		MeshPointer model = this->loadObj(file);
		if(model != 0x0)
		{
			this->models.insert(model, name);
		}
	}
	else if(file.getFileType() == "3ds")
	{
		MeshPointer model = this->load3ds(file);
		if(model != 0x0)
			this->models.insert(model, name);
	}
}

void ResourceManager::addModel(ModelPointer model, char* name)
{
	this->addModel(model, String(name));
}
void ResourceManager::addModel(ModelPointer model, String name)
{
	models.insert(model, name);
}

ModelPointer ResourceManager::getModel(char* name)
{
	return this->getModel(String(name));
}

ModelPointer ResourceManager::getModel(String name)
{
	return models.search(name);
}

MeshPointer ResourceManager::loadObj(File file)
{
	file.open();
	if(!file.isOpen())
	{
		console << "ResourceManager::loadModls error: Failed to open model file " << file.getFullPath() << newline;
		return 0x0;
	}

	String cmd;

	MeshPointer mesh = new Mesh(1);
	MeshPartPointer meshPart = new MeshPart(10);

	// TODO: probably shouldn't start with such large vectors...
	Array<Vector> geometricVectors(10000);
	Array<Vector> textureVectors(10000);
	Array<Vector> normalVectors(10000);
	Array<Vector> parametricVectors(10000);

	Map<MaterialPointer, String> materials;

	String line;
	line = file.getLine();

	Timer timer;
	timer.start();
	bool first = true;
	while(!file.eof())
	{
		line >> cmd;

		switch(cmd[0])
		{
			case 'v':
			{
				float v1, v2, v3;

				if(cmd == "v")
				{
					line >> v1 >> v2 >> v3;
					geometricVectors.insert(Vector(v1, v2, v3));
				}
				else if(cmd == "vt")
				{
					line >> v1 >> v2;
					textureVectors.insert(Vector(v1, v2, 0.0f));
				}
				else if(cmd == "vn")
				{
					line >> v1 >> v2 >> v3;
					normalVectors.insert(Vector(v1, v2, v3));
				}
				else if(cmd == "vp")
				{
					line >> v1 >> v2 >> v3;
					parametricVectors.insert(Vector(v1, v2, v3));
				}
				break;
			}
			case 'f':
			{
				if(first)
				{
					// First 60k of 90k lines takes 3.5 seconds of ~13 seconds
					first = false;
					console << timer.totalTime() << newline;
				}
				String r1, r2, r3;
				line >> r1 >> r2 >> r3;

				bool work = true;
				while(work)
				{
					// Run 1 more iteration after last input then exit
					if(line.length() == 0)
					{
						work = false;
					}

					if(r1.strPos('/') == String::npos)
					{
						int pos = 0;
						Vertex v;

						pos = r1.toInt();
						v.position = geometricVectors[pos - 1];
						meshPart->insert(v);

						pos = r2.toInt();
						v.position = geometricVectors[pos - 1];
						meshPart->insert(v);

						pos = r3.toInt();
						v.position = geometricVectors[pos - 1];
						meshPart->insert(v);
					}
					else
					{
						int pos = 0;
						Array<String> parts;
						Vertex v;

						// Vertex 1
						parts = r1.split('/');
						pos = parts[0].toInt();
						v.position = geometricVectors[pos - 1];
						if(parts[1].length() > 0)
						{
							pos = parts[1].toInt();
							v.texture = textureVectors[pos - 1];
						}
						if(parts.size() > 2 && parts[2].length() > 0)
						{
							pos = parts[2].toInt();
							v.normal = normalVectors[pos - 1];
						}
						meshPart->insert(v);

						// Vertex 2
						parts = r2.split('/');
						pos = parts[0].toInt();
						v.position = geometricVectors[pos - 1];
						if(parts[1].length() > 0)
						{
							pos = parts[1].toInt();
							v.texture = textureVectors[pos - 1];
						}
						if(parts.size() > 2 && parts[2].length() > 0)
						{
							pos = parts[2].toInt();
							v.normal = normalVectors[pos - 1];
						}
						meshPart->insert(v);

						// Vertex 3
						parts = r3.split('/');
						pos = parts[0].toInt();
						v.position = geometricVectors[pos - 1];
						if(parts[1].length() > 0)
						{
							pos = parts[1].toInt();
							v.texture = textureVectors[pos - 1];
						}
						if(parts.size() > 2 && parts[2].length() > 0)
						{
							pos = parts[2].toInt();
							v.normal = normalVectors[pos - 1];
						}
						meshPart->insert(v);
					}

					if(work)
					{
						r2 = r3;
						line >> r3;
					}
				}

				break;
			}
			case 'm':
			{
				if(cmd == "mtllib")
				{
					
					File libraryFile(file.getParentPath() + line);

					try
					{
						materials = this->loadMtl(libraryFile);
					}
					catch(...)
					{
						console << "MeshManage::loadMtl error: Failed to load material file " << libraryFile.getFullPath() << newline;
					}
				}

				break;
			}
			case 'u':
			{
				if(cmd == "usemtl")
				{
					String materialName;
					line >> materialName;

					try
					{
						meshPart->setMaterial(materials.search(materialName));
					}
					catch(...)
					{
						console << "Failed to load " << materialName << newline;
					}

					if(meshPart->size() != 0)
					{
						meshPart->reserve(meshPart->size());
						mesh->insert(meshPart);
						meshPart = new MeshPart(10);
					}
				}

				break;
			}
		}

		line = file.getLine();
	}
	console << timer.totalTime() << newline;

	file.close();

	meshPart->reserve(meshPart->size());
	mesh->insert(meshPart);
	// mesh->reserve(mesh->size());

	mesh->computeBoundingBox();
	return mesh;
}

Map<MaterialPointer, String> ResourceManager::loadMtl(File file)
{
	Map<MaterialPointer, String> materials;

	file.open();
	if(!file.isOpen())
	{
		console << "ResourceManager::loadMtl error: Failed to open material file " << file.getFullPath() << newline;
		return materials;
	}

	String name;
	MaterialPointer material = new Material;

	String line;
	line = file.getLine();

	while(!file.eof())
	{
		String cmd;
		line >> cmd;

		if(cmd == "newmtl")
		{
			if(name != "")
			{
				materials.insert(material, name);
			}

			material = new Material;
			line >> name;
		}
		else if(cmd == "Ka")
		{
			line >> material->ambient[0];
			line >> material->ambient[1];
			line >> material->ambient[2];
		}
		else if(cmd == "Kd")
		{
			line >> material->diffuse[0];
			line >> material->diffuse[1];
			line >> material->diffuse[2];
		}
		else if(cmd == "Ks")
		{
			line >> material->specular[0];
			line >> material->specular[1];
			line >> material->specular[2];
		}
		else if(cmd == "Ns")
		{
			const float DIFF = 128 / 1000;
			line >> material->shininess;
			// Normalize from 0-1000 to 0-128
			material->shininess = material->shininess * DIFF;
		}
		else if(cmd == "Ni")
		{
			line >> material->refraction;
		}
		else if(cmd == "d")
		{
			line >> material->transparency;
		}
		else if(cmd == "Tf")
		{
			line >> material->transmissionFilter[0];
			line >> material->transmissionFilter[1];
			line >> material->transmissionFilter[2];
		}
		else if(cmd == "map_Kd")
		{
			File mapFile(file.getParentPath() + line);
			material->diffuseTexture = this->loadJpeg(mapFile);
		}
		else if(cmd == "map_Ka")
		{
			File mapFile(file.getParentPath() + line);
			material->ambientTexture = this->loadJpeg(mapFile);
		}
		else if(cmd == "map_Ks")
		{
			File mapFile(file.getParentPath() + line);
			material->specularTexture = this->loadJpeg(mapFile);
		}

		line = file.getLine();
	}

	if(name != "")
	{
		materials.insert(material, name);
	}
	
	/*for(Map<MaterialPointer, String>::Iterator it = materials.begin(); !it; it++)
	{
		console << it.key() << newline;
	}*/

	return materials;
}

MeshPointer ResourceManager::load3ds(File file)
{
	file.open();
	if(!file.isOpen())
	{
		console << "ResourceManager::load3ds error: Failed to open model file " << file.getFullPath() << newline;
		return 0x0;
	}
	
	MeshPointer mesh;
	while(!file.eof())
	{
		String data = file.getString(2);
		int length = file.getString(4).binaryTo<int, 4>();
		switch(data[0])
		{
			// Main chunk
			case 0x4D:
			{
				if(data[1] != 0x4D)
					break;
				
				console << "Main Chunk " << length << newline;
				mesh = new Mesh(1);
				break;
			}
			// 3D Editor Chunk
			case 0x3D:
			{
				if(data[1] != 0x3D)
					break;
				
				console << "3D Editor Chunk " << length << newline;
				break;
			}
			// Object Block
			case 0x40:
			{
				
				if(data[1] != 0x00)
					break;
				
				console << "Object Chunk " << length << newline;
				break;
			}
			// Triangular Mesh
			case 0x41:
			{
				if(data[1] != 0x00)
					break;
				
				console << "Triangular Mesh Chunk " << length << newline;
				break;
			}
			// Material Block
			case 0xFF:
			{
				if(data[1] != 0xAF)
					break;
				
				console << "Material Chunk " << length << newline;
				break;
			}
		};
	}
	exit(0);
	
	// Main chunk
	String data = file.getString(2);
	if(data[0] != 0x4D || data[1] != 0x4D)
	{
		console << "ResourceManager::load3ds error: Missing main chunk" << newline;
		return 0x0;
	}
	
	data = file.getString(4);
	int length = data.binaryTo<int, 4>();
	console << "Main chunk: " << length << newline;

	// 3D Editor chunk
	data = file.getString(2);
	if(data[0] != 0x3D || data[1] != 0x3D)
	{
		console << "ResourceManager::load3ds error: Missing 3D Editor chunk" << newline;
	}
	
	exit(0);
	return 0x0;
}

Texture* ResourceManager::loadJpeg(File file)
{
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
	
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);

	FILE* infile;
	int width, height, size;

	if((infile = fopen(file.getFullPath().cStr(), "rb")) == NULL)
	{
		console << "ResourceManager::loadJpeg error: Failed to open jpeg file " << file.getFullPath() << newline;
		return 0x0;
	}

	jpeg_stdio_src(&cinfo, infile);
	jpeg_read_header(&cinfo, TRUE);
	jpeg_start_decompress(&cinfo);

	width = cinfo.output_width * cinfo.output_components;
	height = cinfo.output_height;
	size = width * height;
	
	Texture* bitmap = new Texture(width / 3, height);
	unsigned char* data = bitmap->getPointer();
	
	JSAMPARRAY buffer = new JSAMPROW[1];
	buffer[0] = data;

	while(cinfo.output_scanline < cinfo.output_height)
	{		
		jpeg_read_scanlines(&cinfo, buffer, 1);
		buffer[0] += width;
	}
	
	delete[] buffer;

	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	fclose(infile);

	return bitmap;
}
