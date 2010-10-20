/* 
 * File:   ModelManager.cpp
 * Author: scott
 * 
 * Created on October 20, 2010, 1:25 PM
 */

#include "ModelManager.h"

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
