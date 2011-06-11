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

