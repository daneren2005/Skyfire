/* 
 * File:   ResourceManager.h
 * Author: scott
 *
 * Created on October 20, 2010, 1:25 PM
 */

#ifndef _ResourceManager_H
#define	_ResourceManager_H

#include "Map.h"
#include "Mesh.h"
#include "File.h"
#include "CString.h"
#include "Bitmap.h"

class ResourceManager
{
public:
	ResourceManager();
	ResourceManager(const ResourceManager& orig);
	virtual ~ResourceManager();

	void loadMesh(char* filename, char* name);
	void loadMesh(char* filename, String name);
	void loadMesh(String filename, char* name);
	void loadMesh(String filename, String name);
	void addMesh(Mesh* mesh, char* name);
	void addMesh(Mesh* mesh, String name);
	Mesh* getMesh(char* name);
	Mesh* getMesh(String name);
private:
	Map<String, Mesh*> meshes;

	// Individual filetype load functions
	Mesh* loadObj(File file);
	Map<String, Material*> loadMtl(File file);
	Bitmap* loadJpeg(File file);
};

extern ResourceManager resourceManager;

#endif	/* _ResourceManager_H */

