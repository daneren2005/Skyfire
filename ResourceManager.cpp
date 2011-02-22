/* 
 * File:   ResourceManager.cpp
 * Author: scott
 * 
 * Created on October 20, 2010, 1:25 PM
 */

#include "ResourceManager.h"

#include "conversion.h"

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

void ResourceManager::loadModel(String filename, String name)
{
	File file(filename);

	if(file.fileType() == "obj")
	{
		Model* model = this->loadObj(file);
		if(model != NULL)
		{
			this->models.insert(name, model);
		}
	}
}

void ResourceManager::addModel(Model* model, String name)
{
	models.insert(name, model);
}

Model* ResourceManager::getModel(String name)
{
	return models.search(name);
}

Model* ResourceManager::loadObj(File file)
{
	file.open();
	if(!file.isOpen())
	{
		console << "ResourceManager::loadModls error: Failed to load model from file " << file.fullPath() << newline;
		return NULL;
	}

	String cmd;

	Model* model = new Model(1);
	String modelName;
	int model_i = 0;
	Mesh* mesh = new Mesh(10);
	String meshName;
	int mesh_i = 0;

	Array<Vector> geometricVectors(10);
	int geometric_i = 0;
	Array<Vector> textureVectors(10);
	int texture_i = 0;
	Array<Vector> normalVectors(10);
	int normal_i = 0;
	Array<Vector> parametricVectors(10);
	int parametric_i = 0;

	Map<String, Material*> materials;

	String line;
	line = file.getLine();

	float lx = 1000.0f;
	float ly = 1000.0f;
	float lz = 1000.0f;
	float ux = -1000.0f;
	float uy = -1000.0f;
	float uz = -1000.0f;

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
					geometric_i++;

					// Try to get the bounding box for the model
					if(v1 < lx)
					{
						lx = v1;
					}
					if(v1 > ux)
					{
						ux = v1;
					}

					if(v2 < ly)
					{
						ly = v2;
					}
					if(v2 > uy)
					{
						uy = v2;
					}

					if(v3 < lz)
					{
						lz = v3;
					}
					if(v3 > uz)
					{
						uz = v3;
					}
				}
				else if(cmd == "vt")
				{
					line >> v1 >> v2;
					textureVectors.insert(Vector(v1, v2, 0.0f));
					texture_i++;
				}
				else if(cmd == "vn")
				{
					line >> v1 >> v2 >> v3;
					normalVectors.insert(Vector(v1, v2, v3));
					normal_i++;
				}
				else if(cmd == "vp")
				{
					line >> v1 >> v2 >> v3;
					parametricVectors.insert(Vector(v1, v2, v3));
					parametric_i++;
				}
				break;
			}
			case 'f':
			{
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

					// Array<String> parts = r1.split('/');
					int pos = r1.strPos('/');
					if(pos == String::npos)
					{
						int rg1, rg2, rg3;
						rg1 = r1.toInt();
						Vertex v1;
						v1.position[0] = geometricVectors[rg1 - 1][0];
						v1.position[1] = geometricVectors[rg1 - 1][1];
						v1.position[2] = geometricVectors[rg1 - 1][2];
						mesh->insert(v1);
						mesh_i++;
						rg2 = r2.toInt();
						Vertex v2;
						v2.position[0] = geometricVectors[rg2 - 1][0];
						v2.position[1] = geometricVectors[rg2 - 1][1];
						v2.position[2] = geometricVectors[rg2 - 1][2];
						mesh->insert(v2);
						mesh_i++;
						rg3 = r3.toInt();
						Vertex v3;
						v3.position[0] = geometricVectors[rg3 - 1][0];
						v3.position[1] = geometricVectors[rg3 - 1][1];
						v3.position[2] = geometricVectors[rg3 - 1][2];
						mesh->insert(v3);
						mesh_i++;
					}
					else
					{
						int rg1, rg2, rg3;
						int rn1, rn2, rn3;
						int rt1, rt2, rt3;
						rg1 = r1.subStr(0, pos).toInt();
						Vertex v1;
						v1.position[0] = geometricVectors[rg1 - 1][0];
						v1.position[1] = geometricVectors[rg1 - 1][1];
						v1.position[2] = geometricVectors[rg1 - 1][2];
						mesh->insert(v1);
						mesh_i++;

						pos = r2.strPos('/');
						rg2 = r2.subStr(0, pos).toInt();
						Vertex v2;
						v2.position[0] = geometricVectors[rg2 - 1][0];
						v2.position[1] = geometricVectors[rg2 - 1][1];
						v2.position[2] = geometricVectors[rg2 - 1][2];
						mesh->insert(v2);
						mesh_i++;

						pos = r3.strPos('/');
						rg3 = r3.subStr(0, pos).toInt();
						Vertex v3;
						v3.position[0] = geometricVectors[rg3 - 1][0];
						v3.position[1] = geometricVectors[rg3 - 1][1];
						v3.position[2] = geometricVectors[rg3 - 1][2];
						mesh->insert(v3);
						mesh_i++;
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
					String libraryFileName;
					line >> libraryFileName;
					File libraryFile(file.filePath() + libraryFileName);

					try
					{
						materials = this->loadMtl(libraryFile);
					}
					catch(...)
					{
						console << "ModelManage::loadMtl error: Failed to load material file " << libraryFile.fullPath() << newline;
					}
				}

				break;
			}
			case 'u':
			{
				if(cmd == "usemtl")
				{
					String materialName2;
					line >> materialName2;

					try
					{
						Material* temp = materials.search(materialName2);
						mesh->material = *temp;
					}
					catch(...)
					{
						mesh->setWireFrame(true);
					}

					if(mesh->size() != 0)
					{
						mesh->resize(mesh->size());
						model->insert(mesh);
						model_i++;
						mesh = new Mesh(10);
						mesh_i = 0;
					}
				}

				break;
			}
		}

		line = file.getLine();
	}

	file.close();

	mesh->resize(mesh->size());
	model->insert(mesh);
	model->resize(model->size());

	model->setBoundingBox(Rectangle3(lx, ly, lz, ux, uy, uz));
	return model;
}

Map<String, Material*> ResourceManager::loadMtl(File file)
{
	Map<String, Material*> materials;

	file.open();
	if(!file.isOpen())
	{
		console << "ModelManage::loadMtl error: Failed to load material file " << file.fullPath() << newline;
		return materials;
	}

	String name;
	Material* material = new Material;

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
				materials.insert(name, material);
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
			line >> material->transmissionFiler[0];
			line >> material->transmissionFiler[1];
			line >> material->transmissionFiler[2];
		}

		line = file.getLine();
	}

	if(name != "")
	{
		materials.insert(name, material);
	}

	return materials;
}
