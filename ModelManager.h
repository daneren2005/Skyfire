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
#include "CString.h"

class ModelManager
{
public:
	ModelManager();
	ModelManager(const ModelManager& orig);
	virtual ~ModelManager();

	void loadModels(String filename);
	void addModel(Model* model, String name);
	Model* getModel(String name);
private:
	Map<String, Model*> models;

	void loadObj(String filename);
	Map<String, Material*> loadMtl(String filename);
};

extern ModelManager modelManager;

#endif	/* _MODELMANAGER_H */

