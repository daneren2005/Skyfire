/* 
 * File:   ModelManager.cpp
 * Author: scott
 * 
 * Created on October 20, 2010, 1:25 PM
 */

#include "ModelManager.h"

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
	std::ifstream file;
	file.open(filename.c_str());

	if(!file.good())
	{
		std::cout << "ModelManager::loadModels error: Failed to load " << filename << std::endl;
		return;
	}

	std::string cmd;

	Mesh* mesh = new Mesh(10);
	int mesh_i = 0;

	Array<Vector> vectors(10);
	int vector_i = 0;

	std::string name = "";
	float v1, v2, v3;
	int r1, r2, r3;
	
	char line[256];
	file.getline(line, 256);

	while(file.good())
	{
		std::string lineString(line);
		std::stringstream ss;
		ss << lineString;

		ss >> cmd;

		switch(cmd[0])
		{
			// Group naming
			case 'g':
				// If exiting one group to enter another
				if(name != "")
				{
					mesh = new Mesh(100);
					mesh_i = 0;
				}

				ss >> name;
				break;
			case 'v':
				ss >> v1 >> v2 >> v3;
				vectors[vector_i] = Vector(v1, v2, v3);
				vector_i++;
				break;
			case 'f':
				ss >> r1 >> r2 >> r3;
				(*mesh)[mesh_i] = Triangle(vectors[r1 - 1], vectors[r2 - 1], vectors[r3 - 1], Vector(1.0f, 0.0f, 0.0f));
				mesh_i++;

				break;
		}

		file.getline(line, 256);
	}

	// std::cout << name << std::endl;
	meshes.insert(name, mesh);
}

void ModelManager::addModel(Mesh* model, std::string name)
{
	meshes.insert(name, model);
}

Mesh* ModelManager::getModel(std::string name)
{
	return meshes.get(name);
}

void ModelManager::compileModels()
{

}

void ModelManager::loadObj(std::string filename)
{
	
}
