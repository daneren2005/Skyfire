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

void ModelManager::loadModels(std::string filename)
{
	this->loadObj(filename);
}

void ModelManager::addModel(Model* model, std::string name)
{
	models.insert(name, model);
}

Model* ModelManager::getModel(std::string name)
{
	return models.get(name);
}

void ModelManager::loadObj(std::string filename)
{
	std::ifstream file;
	file.open(filename.c_str());

	if(!file.good())
	{
		std::cout << "ModelManager::loadModels error: Failed to load " << filename << std::endl;
		return;
	}

	std::string cmd;

	Model* model = new Model(1);
	std::string modelName = "";
	int model_i = 0;
	Mesh* mesh = new Mesh(10);
	std::string meshName = "";
	int mesh_i = 0;

	Array<Vector> geometricVectors(10);
	int geometric_i = 0;
	Array<Vector> textureVectors(10);
	int texture_i = 0;
	Array<Vector> normalVectors(10);
	int normal_i = 0;
	Array<Vector> parametricVectors(10);
	int parametric_i = 0;

	Map<std::string, Material*> materials;
	
	char line[10240];
	file.getline(line, 10240);

	while(file.good())
	{
		std::string lineString(line);
		std::stringstream ss;
		ss << lineString;

		cmd = "";
		ss >> cmd;

		switch(cmd[0])
		{
			// Object naming
			case 'o':
			{
				// If exiting one object to enter another
				if(modelName != "")
				{
					mesh->resize(mesh_i + 1);
					(*model)[model_i] = *mesh;
					model = new Model(10);
					model_i = 0;
					mesh = new Mesh(10);
					mesh_i = 0;
				}

				ss >> modelName;
				break;
			}
			case 'g':
			{
				if(meshName != "")
				{
					mesh->resize(mesh_i + 1);
					(*model)[model_i] = *mesh;
					model_i++;
					mesh = new Mesh(10);
					mesh_i = 0;
				}

				ss >> meshName;
				break;
			}
			case 'v':
			{
				float v1, v2, v3;

				if(cmd.length() == 1)
				{
					ss >> v1 >> v2 >> v3;
					geometricVectors[geometric_i] = Vector(v1, v2, v3);
					geometric_i++;
				}
				else
				{
					switch(cmd[1])
					{
					case 't':
						ss >> v1 >> v2;
						textureVectors[texture_i] = Vector(v1, v2, 0.0f);
						texture_i++;
						break;
					case 'n':
						ss >> v1 >> v2 >> v3;
						normalVectors[normal_i] = Vector(v1, v2, v3);
						normal_i++;
						break;
					case 'p':
						ss >> v1 >> v2 >> v3;
						parametricVectors[parametric_i] = Vector(v1, v2, v3);
						parametric_i++;
						break;
					};
				}
				break;
			}
			case 'f':
			{
				std::string r1, r2, r3;
				ss >> r1 >> r2 >> r3;

				bool work = true;
				while(work)
				{
					// Run 1 more iteration after last input then exit
					if(ss.eof())
					{
						work = false;
					}

					int pos = r1.find_first_of('/');
					if(pos == std::string::npos)
					{
						int rg1, rg2, rg3;
						rg1 = atof(r1.c_str());
						(*mesh)[mesh_i].position[0] = geometricVectors[rg1 - 1][0];
						(*mesh)[mesh_i].position[1] = geometricVectors[rg1 - 1][1];
						(*mesh)[mesh_i].position[2] = geometricVectors[rg1 - 1][2];
						mesh_i++;
						rg2 = atof(r2.c_str());
						(*mesh)[mesh_i].position[0] = geometricVectors[rg2 - 1][0];
						(*mesh)[mesh_i].position[1] = geometricVectors[rg2 - 1][1];
						(*mesh)[mesh_i].position[2] = geometricVectors[rg2 - 1][2];
						mesh_i++;
						rg3 = atof(r3.c_str());
						(*mesh)[mesh_i].position[0] = geometricVectors[rg3 - 1][0];
						(*mesh)[mesh_i].position[1] = geometricVectors[rg3 - 1][1];
						(*mesh)[mesh_i].position[2] = geometricVectors[rg3 - 1][2];
						mesh_i++;
					}
					else
					{
						int rg1, rg2, rg3;
						int rn1, rn2, rn3;
						int rt1, rt2, rt3;
						rg1 = atof(r1.substr(0, pos + 1).c_str());
						(*mesh)[mesh_i].position[0] = geometricVectors[rg1 - 1][0];
						(*mesh)[mesh_i].position[1] = geometricVectors[rg1 - 1][1];
						(*mesh)[mesh_i].position[2] = geometricVectors[rg1 - 1][2];
						mesh_i++;

						pos = r2.find_first_of('/');
						rg2 = atof(r2.substr(0, pos + 1).c_str());
						(*mesh)[mesh_i].position[0] = geometricVectors[rg2 - 1][0];
						(*mesh)[mesh_i].position[1] = geometricVectors[rg2 - 1][1];
						(*mesh)[mesh_i].position[2] = geometricVectors[rg2 - 1][2];
						mesh_i++;

						pos = r3.find_first_of('/');
						rg3 = atof(r3.substr(0, pos + 1).c_str());
						(*mesh)[mesh_i].position[0] = geometricVectors[rg3 - 1][0];
						(*mesh)[mesh_i].position[1] = geometricVectors[rg3 - 1][1];
						(*mesh)[mesh_i].position[2] = geometricVectors[rg3 - 1][2];
						mesh_i++;
					}

					if(work)
					{
						r2 = r3;
						ss >> r3;
					}
				}

				break;
			}
			case 'm':
			{
				if(cmd == "mtllib")
				{
					std::string libraryFileName;
					ss >> libraryFileName;
					libraryFileName = "data/Danube/" + libraryFileName;

					materials = this->loadMtl(libraryFileName);
				}

				break;
			}
			case 'u':
			{
				if(cmd == "usemtl")
				{
					std::string materialName;
					ss >> materialName;

					Material* temp = materials[materialName];
					if(temp != NULL)
					{
						mesh->material = *temp;
					}

					if(meshName != "")
					{
						mesh->resize(mesh_i + 1);
						(*model)[model_i] = *mesh;
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

	mesh->resize(mesh_i + 1);
	(*model)[model_i] = *mesh;
	model->resize(model_i + 1);
	if(modelName != "")
	{
		models.insert(modelName, model);
	}
	else
	{
		models.insert(meshName, model);
	}
}

Map<std::string, Material*> ModelManager::loadMtl(std::string filename)
{
	Map<std::string, Material*> materials;

	std::ifstream file;
	file.open(filename.c_str());

	if(!file.good())
	{
		std::cout << "ModelManager::loadModels error: Failed to load file " << filename << std::endl;
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
				materials.insert(name, material);
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

		file.getline(line, 128);
	}

	return materials;
}
