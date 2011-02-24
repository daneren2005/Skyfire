/*
 * File:   ResourceManager.cpp
 * Author: scott
 *
 * Created on October 20, 2010, 1:25 PM
 */

#include "ResourceManager.h"

#include "conversion.h"

// Jpeg library
#include "jpeglib.h"
#include "setjmp.h"

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

void ResourceManager::loadModel(char* filename, char* name)
{
	this->loadModel(String(filename), String(name));
}
void ResourceManager::loadModel(char* filename, String name)
{
	this->loadModel(String(filename), name);
}
void ResourceManager::loadModel(String filename, char* name)
{
	this->loadModel(filename, String(name));
}
void ResourceManager::loadModel(String filename, String name)
{
	File file(filename);

	if(file.fileType() == "obj")
	{
		Model* model = this->loadObj(file);
		if(model != 0x0)
		{
			this->models.insert(name, model);
		}
	}
}

void ResourceManager::addModel(Model* model, char* name)
{
	this->addModel(model, String(name));
}
void ResourceManager::addModel(Model* model, String name)
{
	models.insert(name, model);
}

Model* ResourceManager::getModel(char* name)
{
	return this->getModel(String(name));
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
		console << "ResourceManager::loadModls error: Failed to open model file " << file.fullPath() << newline;
		return 0x0;
	}

	String cmd;

	Model* model = new Model(1);
	String modelName;
	int model_i = 0;
	Mesh* mesh = new Mesh(10);
	String meshName;
	int mesh_i = 0;

	Array<Vector> geometricVectors(10);
	Array<Vector> textureVectors(10);
	Array<Vector> normalVectors(10);
	Array<Vector> parametricVectors(10);

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
				}
				else if(cmd == "vn")
				{
					line >> v1 >> v2 >> v3;
					normalVectors.insert(Vector(v1, v2, v3));
				}
				else if(cmd == "vp")
				{
					line >> v1 >> v2 >> v3;
					parametricVectors.insert(Vector(v1, v2, v3));
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

					if(r1.strPos('/') == String::npos)
					{
						int pos = 0;
						Vertex v;

						pos = r1.toInt();
						v.position = geometricVectors[pos - 1];
						mesh->insert(v);

						pos = r2.toInt();
						v.position = geometricVectors[pos - 1];
						mesh->insert(v);

						pos = r3.toInt();
						v.position = geometricVectors[pos - 1];
						mesh->insert(v);
					}
					else
					{
						int pos = 0;
						Array<String> parts;
						Vertex v;

						// Vertex 1
						parts = r1.split('/');
						pos = parts[0].toInt();
						v.position = geometricVectors[pos - 1];
						if(parts[1].length() > 0)
						{
							pos = parts[1].toInt();
							v.texture = textureVectors[pos - 1];
						}
						if(parts[2].length() > 0)
						{
							pos = parts[2].toInt();
							v.normal = normalVectors[pos - 1];
						}
						mesh->insert(v);

						// Vertex 2
						parts = r2.split('/');
						pos = parts[0].toInt();
						v.position = geometricVectors[pos - 1];
						if(parts[1].length() > 0)
						{
							pos = parts[1].toInt();
							v.texture = textureVectors[pos - 1];
						}
						if(parts[2].length() > 0)
						{
							pos = parts[2].toInt();
							v.normal = normalVectors[pos - 1];
						}
						mesh->insert(v);

						// Vertex 3
						parts = r3.split('/');
						pos = parts[0].toInt();
						v.position = geometricVectors[pos - 1];
						if(parts[1].length() > 0)
						{
							pos = parts[1].toInt();
							v.texture = textureVectors[pos - 1];
						}
						if(parts[2].length() > 0)
						{
							pos = parts[2].toInt();
							v.normal = normalVectors[pos - 1];
						}
						mesh->insert(v);
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
		console << "ResourceManager::loadMtl error: Failed to open material file " << file.fullPath() << newline;
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
		else if(cmd == "map_Kd")
		{
			String filename;
			line >> filename;
			File mapFile(file.filePath() + filename);
			material->diffuseMap = this->loadJpeg(mapFile);
		}
		/*else if(cmd == "map_bump")
		{
			String filename;
			line >> filename;
			File mapFile(file.filePath() + filename);
			this->loadJpeg(mapFile);
		}*/
		/*else if(cmd == "bump")
		{
			String filename;
			line >> filename;
			File mapFile(file.filePath() + filename);
			this->loadJpeg(mapFile);
		}*/

		line = file.getLine();
	}

	if(name != "")
	{
		materials.insert(name, material);
	}

	return materials;
}

// Temporary crap
struct my_error_mgr {
  struct jpeg_error_mgr pub;	/* "public" fields */

  jmp_buf setjmp_buffer;	/* for return to caller */
};

typedef struct my_error_mgr * my_error_ptr;

METHODDEF(void)
my_error_exit (j_common_ptr cinfo)
{
  /* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
  my_error_ptr myerr = (my_error_ptr) cinfo->err;

  /* Always display the message. */
  /* We could postpone this until after returning, if we chose. */
  (*cinfo->err->output_message) (cinfo);
  console << "ResourceManager::loadJpeg error: unknown error reading jpeg file" << newline;

  /* Return control to the setjmp point */
  longjmp(myerr->setjmp_buffer, 1);
}

Bitmap* ResourceManager::loadJpeg(File file)
{
	struct jpeg_decompress_struct cinfo;
	struct my_error_mgr jerr;

	FILE* infile;
	JSAMPARRAY buffer;
	int row_stride;

	if((infile = fopen(file.fullPath().cStr(), "rb")) == NULL)
	{
		console << "ResourceManager::loadJpeg error: Failed to open jpeg file " << file.fullPath() << newline;
		return 0x0;
	}

	cinfo.err = jpeg_std_error(&jerr.pub);
	jerr.pub.error_exit = my_error_exit;
	if (setjmp(jerr.setjmp_buffer))
	{
		console << "ResourceManager::loadJpeg error: unknown error reading jpeg file " << file.fullPath() << newline;

		jpeg_destroy_decompress(&cinfo);
		fclose(infile);
		return 0x0;
	}

	jpeg_create_decompress(&cinfo);
	jpeg_stdio_src(&cinfo, infile);
	jpeg_read_header(&cinfo, TRUE);
	jpeg_start_decompress(&cinfo);
	row_stride = cinfo.output_width * cinfo.output_components;
	buffer = (*cinfo.mem->alloc_sarray) ((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);

	Bitmap* bitmap = new Bitmap(cinfo.output_width, cinfo.output_height);
	while (cinfo.output_scanline < cinfo.output_height)
	{
		jpeg_read_scanlines(&cinfo, buffer, 1);
		// put_scanline_someplace(buffer[0], row_stride);
	}

	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	fclose(infile);

	return bitmap;
}
