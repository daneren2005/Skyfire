/* 
 * File:   ModelManager.cpp
 * Author: scott
 * 
 * Created on October 20, 2010, 1:25 PM
 */

#include "ModelManager.h"

#include "conversion.h"
#include <fstream>
#include <sstream>
#include "File.h"

ModelManager modelManager = ModelManager();

ModelManager::ModelManager()
{
}

ModelManager::ModelManager(const ModelManager& orig)
{
}

ModelManager::~ModelManager()
{
}

void ModelManager::loadModels(String filename)
{
	this->loadObj(filename);
}

void ModelManager::addModel(Model* model, String name)
{
	models.insert(name, model);
}

Model* ModelManager::getModel(String name)
{
	return models.search(name);
}

void ModelManager::loadObj(String filename)
{
	std::ifstream file;
	file.open(filename.cStr());

	if(!file.good())
	{
		console << "ModelManager::loadModels error: Failed to load " << filename << newline;
		return;
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
	
	char line[10240];
	file.getline(line, 10240);

	float lx = 1000.0f;
	float ly = 1000.0f;
	float lz = 1000.0f;
	float ux = -1000.0f;
	float uy = -1000.0f;
	float uz = -1000.0f;

	while(file.good())
	{
		String lineString(line);
		lineString >> cmd;

		switch(cmd[0])
		{
			// Object naming
			case 'o':
			{
				// If exiting one object to enter another
				if(modelName != "")
				{
					// mesh->resize(mesh->size());
					model->insert(mesh);
					model = new Model(10);
					model_i = 0;
					mesh = new Mesh(10);
					mesh_i = 0;
				}

				lineString >> modelName;
				break;
			}
			case 'g':
			{
				if(meshName != "")
				{
					model->insert(mesh);
					model_i++;
					mesh = new Mesh(10);
					mesh_i = 0;
				}

				lineString >> meshName;
				break;
			}
			case 'v':
			{
				float v1, v2, v3;

				if(cmd == "v")
				{
					lineString >> v1 >> v2 >> v3;
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
					lineString >> v1 >> v2;
					textureVectors.insert(Vector(v1, v2, 0.0f));
					texture_i++;
				}
				else if(cmd == "vn")
				{
					lineString >> v1 >> v2 >> v3;
					normalVectors.insert(Vector(v1, v2, v3));
					normal_i++;
				}
				else if(cmd == "vp")
				{
					lineString >> v1 >> v2 >> v3;
					parametricVectors.insert(Vector(v1, v2, v3));
					parametric_i++;
				}
				break;
			}
			case 'f':
			{
				String r1, r2, r3;
				lineString >> r1 >> r2 >> r3;

				bool work = true;
				while(work)
				{
					// Run 1 more iteration after last input then exit
					if(lineString.length() == 0)
					{
						work = false;
					}

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
						lineString >> r3;
					}
				}

				break;
			}
			case 'm':
			{
				if(cmd == "mtllib")
				{
					String libraryFileName2;
					lineString >> libraryFileName2;
					libraryFileName2 = String("data/Danube/") + libraryFileName2;

					materials = this->loadMtl(libraryFileName2);
				}

				break;
			}
			case 'u':
			{
				if(cmd == "usemtl")
				{
					String materialName2;
					lineString >> materialName2;

					try
					{
						Material* temp = materials.search(materialName2);
						mesh->material = *temp;
					}
					catch(...)
					{
						mesh->setWireFrame(true);
					}

					if(meshName != "" && mesh->size() != 0)
					{
						// mesh->resize(mesh->size());
						model->insert(mesh);
						model_i++;
						mesh = new Mesh(10);
						mesh_i = 0;
					}
					// mesh->material.ambient[0] = 1.0f;
				}

				break;
			}
		}

		file.getline(line, 10240);
	}

	mesh->resize(mesh->size());
	model->insert(mesh);
	model->resize(model->size());

	model->setBoundingBox(Rectangle3(lx, ly, lz, ux, uy, uz));

	if(modelName != "")
	{
		models.insert(modelName, model);
	}
	else
	{
		models.insert(meshName, model);
	}
}

Map<String, Material*> ModelManager::loadMtl(String filename)
{
	Map<String, Material*> materials;

	std::ifstream file;
	file.open(filename.cStr());

	if(!file.good())
	{
		std::cout << "ModelManager::loadModels error: Failed to load file " << filename.cStr() << std::endl;
		return materials;
	}

	std::string name = "";
	Material* material = new Material;

	char line[128];
	file.getline(line, 128);

	while(file.good())
	{
		std::string lineString(line);
		std::stringstream ss;
		ss << lineString;

		std::string cmd;
		ss >> cmd;

		if(cmd == "newmtl")
		{
			if(name != "")
			{
				materials.insert(String(name.c_str()), material);
			}

			material = new Material;
			ss >> name;
		}
		else if(cmd == "Ka")
		{
			float r1, r2, r3;
			ss >> r1 >> r2 >> r3;
			material->ambient[0] = r1;
			material->ambient[1] = r2;
			material->ambient[2] = r3;
		}
		else if(cmd == "Kd")
		{
			float r1, r2, r3;
			ss >> r1 >> r2 >> r3;
			material->diffuse[0] = r1;
			material->diffuse[1] = r2;
			material->diffuse[2] = r3;
		}
		else if(cmd == "Ks")
		{
			float r1, r2, r3;
			ss >> r1 >> r2 >> r3;
			material->specular[0] = r1;
			material->specular[1] = r2;
			material->specular[2] = r3;
		}
		else if(cmd == "Ns")
		{
			const float DIFF = 128 / 1000;
			ss >> material->shininess;
			// Normalize from 0-1000 to 0-128
			material->shininess = material->shininess * DIFF;
		}
		else if(cmd == "Ni")
		{
			ss >> material->refraction;
		}
		else if(cmd == "d")
		{
			ss >> material->transparency;
		}
		else if(cmd == "Tf")
		{
			ss >> material->transmissionFiler[0];
			ss >> material->transmissionFiler[1];
			ss >> material->transmissionFiler[2];
		}

		file.getline(line, 128);
	}

	if(name != "")
	{
		materials.insert(String(name.c_str()), material);
	}

	return materials;
}
