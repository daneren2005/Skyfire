/* 
 * File:   ModelManager.h
 * Author: scott
 *
 * Created on October 20, 2010, 1:25 PM
 */

#ifndef _MODELMANAGER_H
#define	_MODELMANAGER_H

#include "Map.h"
#include "Model.h"
#include <iostream>

class ModelManager
{
public:
	ModelManager();
	ModelManager(const ModelManager& orig);
	virtual ~ModelManager();

	void loadModels(std::string filename);
	void addModel(Mesh* model, std::string name);
	void compileModels();
	Mesh* getModel(std::string name);
private:
	Map<std::string, Mesh*> meshes;

	void loadObj(std::string filename);
};

extern ModelManager modelManager;

#endif	/* _MODELMANAGER_H */

