/* 
 * File:   ResourceManager.h
 * Author: scott
 *
 * Created on October 20, 2010, 1:25 PM
 */

#ifndef _ResourceManager_H
#define	_ResourceManager_H

#include "Map.h"
#include "Model.h"
#include "File.h"
#include "CString.h"
#include "Bitmap.h"

class ResourceManager
{
public:
	ResourceManager();
	ResourceManager(const ResourceManager& orig);
	virtual ~ResourceManager();

	void loadModel(char* filename, char* name);
	void loadModel(char* filename, String name);
	void loadModel(String filename, char* name);
	void loadModel(String filename, String name);
	void addModel(Model* model, char* name);
	void addModel(Model* model, String name);
	Model* getModel(char* name);
	Model* getModel(String name);
private:
	Map<String, Model*> models;

	// Individual filetype load functions
	Model* loadObj(File file);
	Map<String, Material*> loadMtl(File file);
	Bitmap* loadJpeg(File file);
};

extern ResourceManager resourceManager;

#endif	/* _ResourceManager_H */

