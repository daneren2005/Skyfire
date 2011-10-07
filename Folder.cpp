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

#include "Folder.h"
#include "Exceptions.h"

#ifdef WIN32
	#include <direct.h>
#endif
#ifdef __linux__
	#include <unistd.h>
	#include <dirent.h>
	#include <sys/stat.h>
#endif

Folder::Folder()
{
	char* buffer = new char[BUFFER_SIZE];
	if(getcwd(buffer, BUFFER_SIZE) == 0x0)
	{
		delete buffer;
		buffer = new char[BACKUP_BUFFER_SIZE];
		if(getcwd(buffer, BACKUP_BUFFER_SIZE) == 0x0)
		{
			throw Exception(String("Error: Current directory is more than ") + String(BACKUP_BUFFER_SIZE) + String(" characters long"));
		}
	}

	this->currDir = String(buffer);
	delete buffer;
}
Folder::Folder(const String& location)
{
	if(location[0] == '/')
		this->currDir = location;
	else
		this->currDir = Folder::getCWD() + "/" + location;
}

Folder::Folder(const Folder& orig)
{
	this->currDir = orig.currDir;
}

Folder::~Folder()
{
}

String Folder::getPath() const
{
	return this->currDir;
}
Folder Folder::getParentFolder() const
{
	long pos = currDir.strLastPos("/");
	if(pos == 0)
		return Folder(String("/"));
	else
		return Folder(currDir.subStr(0, pos));
}
Folder Folder::getRootFolder() const
{
	Array<long> positions = currDir.strAllPos('/');
	return Folder(currDir.subStr(0, positions[1]));
}
void Folder::changeLocation(const String& newLocation)
{
	// Completely new location
	if(newLocation[0] == '/')
	{
		currDir = newLocation;
	}
	else
	{
		currDir += String("/") + newLocation;

		long pos = currDir.strPos("..");
		while(pos != String::npos)
		{
			Array<long> positions = currDir.strAllPos('/');
			int i;
			for(i = positions.size() - 1; i >= 0 && positions[i] > pos; i--);

			if(pos + 2 >= currDir.length())
				currDir = currDir.subStr(0, positions[i - 1]);
			else
				currDir = currDir.subStr(0, positions[i - 1]) + currDir.subStr(positions[i + 1]);

			pos = currDir.strPos("..");
		}
	}

	if(currDir[currDir.length() - 1] == '/')
		currDir = currDir.subStr(0, currDir.length() - 1);
}

bool Folder::canRead() const
{
	#ifdef WIN32
		// TODO: fill out
	#endif
	#ifdef __linux__
		return access(currDir.cStr(), R_OK) == 0;
	#endif
}
bool Folder::canWrite() const
{
	#ifdef WIN32
		// TODO: fill out
	#endif
	#ifdef __linux__
		return access(currDir.cStr(), W_OK) == 0;
	#endif
}
bool Folder::canExecute() const
{
	#ifdef WIN32
		// TODO: fill out
	#endif
	#ifdef __linux__
		return access(currDir.cStr(), X_OK) == 0;
	#endif
}

int Folder::getPermissions() const
{
	#ifdef WIN32
		// TODO: fill out
	#endif
	#ifdef __linux__
		struct stat statBuffer;
		if(stat(currDir.cStr(), &statBuffer) != 0)
			return 0;
	
		return ((statBuffer.st_mode & S_IRWXU) >> 6) * 100 + ((statBuffer.st_mode & S_IRWXG) >> 3) * 10 + (statBuffer.st_mode & S_IRWXO);
	#endif
}
int Folder::getOwnerPermissions() const
{
	#ifdef WIN32
		// TODO: fill out
	#endif
	#ifdef __linux__
		struct stat statBuffer;
		if(stat(currDir.cStr(), &statBuffer) != 0)
			return 0;
	
		return (statBuffer.st_mode & S_IRWXU) >> 6;
	#endif
}
int Folder::getGroupPermissions() const
{
	#ifdef WIN32
		// TODO: fill out
	#endif
	#ifdef __linux__
		struct stat statBuffer;
		if(stat(currDir.cStr(), &statBuffer) != 0)
			return 0;
	
		return (statBuffer.st_mode & S_IRWXG) >> 3;
	#endif
}
int Folder::getOtherPermissions() const
{
	#ifdef WIN32
		// TODO: fill out
	#endif
	#ifdef __linux__
		struct stat statBuffer;
		if(stat(currDir.cStr(), &statBuffer) != 0)
			return 0;
	
		return statBuffer.st_mode & S_IRWXO;
	#endif
}
int Folder::getOwnerID() const
{
	#ifdef WIN32
		// TODO: fill out
	#endif
	#ifdef __linux__
		struct stat statBuffer;
		if(stat(currDir.cStr(), &statBuffer) != 0)
			return 0;
	
		return statBuffer.st_uid;
	#endif
}
int Folder::getGroupID() const
{
	#ifdef WIN32
		// TODO: fill out
	#endif
	#ifdef __linux__
		struct stat statBuffer;
		if(stat(currDir.cStr(), &statBuffer) != 0)
			return 0;
	
		return statBuffer.st_gid;
	#endif
}

bool Folder::doesExist() const
{
	#ifdef WIN32
		// TODO: fill out
	#endif
	#ifdef __linux__
		return access(currDir.cStr(), F_OK) == 0;
	#endif
}

Array<File> Folder::getFiles() const
{
	Array<File> array;

	#ifdef WIN32
		WIN32_FIND_DATA findData;
		HANDLE fileHandle;

		fileHandle = FindFirstFile(currDir.cStr(), &findData);
		if(fileHandle == INVALID_HANDLE_VALUE)
			return array;

		do
		{
			String filePath = currDir + "/" + fileData.cFileName;
			String fileName(fileData.cFileName);

			if(fileData.dwFileAttributes & FILE_ATTRIBUTE_NORMAL)
			{
				File file(filePath);
				array.insert(file);
			}
		} while(FindNextFile(fileHandle, &findData));
		FindClose(fileHandle);
	#endif
	#ifdef __linux__
		DIR* dir;
		struct dirent* entry;
		struct stat statBuffer;

		dir = opendir(currDir.cStr());
		while((entry = readdir(dir)) != 0x0)
		{
			String filePath = currDir + "/" + entry->d_name;
			String fileName(entry->d_name);

			stat(filePath.cStr(), &statBuffer);
			if(S_ISREG(statBuffer.st_mode) == true)
			{
				File file(filePath);
				array.insert(file);
			}
		}
		closedir(dir);
	#endif

	return array;
}
Array<Folder> Folder::getFolders() const
{
	Array<Folder> array;

	#ifdef WIN32
		WIN32_FIND_DATA findData;
		HANDLE fileHandle;

		fileHandle = FindFirstFile(currDir.cStr(), &findData);
		if(fileHandle == INVALID_HANDLE_VALUE)
			return array;

		do
		{
			String filePath = currDir + "/" + fileData.cFileName;
			String fileName(fileData.cFileName);

			if(fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				Folder folder(filePath);
				array.insert(folder);
			}
		} while(FindNextFile(fileHandle, &findData));
		FindClose(fileHandle);
	#endif
	#ifdef __linux__
		DIR* dir;
		struct dirent* entry;
		struct stat statBuffer;

		dir = opendir(currDir.cStr());
		while((entry = readdir(dir)) != 0x0)
		{
			String filePath = currDir + "/" + entry->d_name;
			String fileName(entry->d_name);

			stat(filePath.cStr(), &statBuffer);
			if(S_ISDIR(statBuffer.st_mode) == true && fileName != ".." && fileName != ".")
			{
				Folder folder(filePath);
				array.insert(folder);
			}
		}
		closedir(dir);
	#endif

	return array;
}

File Folder::getFile(String name)
{
	if(name[0] != '/')
		name = this->currDir + "/" + name;

	return File(name);
}
File Folder::createFile(String name)
{
	if(name[0] != '/')
		name = this->currDir + "/" + name;

	File file(name);
	if(file.doesExist())
	{
		return file;
	}

	file.open(File::WRITE);
	file.close();
	return file;
}

Folder Folder::getSubFolder(String name)
{
	if(name[0] != '/')
		name = this->currDir + "/" + name;

	return Folder(name);
}
Folder Folder::createSubFolder(String name)
{
	if(name[0] != '/')
		name = this->currDir + "/" + name;

	Folder folder(name);
	if(folder.doesExist())
	{
		return folder;
	}

	#ifdef WIN32
		// TODO: fill out
	#endif
	#ifdef __linux__
		if(mkdir(name.cStr(), 0700) != 0)
		{
			throw InvalidFolder(name);
		}
	#endif

	return folder;
}

long Folder::getSize() const
{
	long totalBytes = 0;

	Array<File> files = this->getFiles();
	for(unsigned long i = 0; i < files.size(); i++)
	{
		// cout << files[i].getFullPath().cStr() << " " << files[i].getSize() << endl;
		totalBytes += files[i].getSize();
	}

	Array<Folder> folders = this->getFolders();
	for(unsigned long i = 0; i < folders.size(); i++)
	{
		// cout << folders[i].getPath().cStr() << endl;
		totalBytes += folders[i].getSize();
	}

	#ifdef WIN32
		// TODO: fill out
	#endif
	#ifdef __linux__
		struct stat statBuffer;
		stat(currDir.cStr(), &statBuffer);
		totalBytes += statBuffer.st_size;
	#endif

	return totalBytes;
}
double Folder::getSizeKB() const
{
	return this->getSize() / 1024.0;
}
double Folder::getSizeMB() const
{
	return this->getSize() / 1048576.0;
}
double Folder::getSizeGB() const
{
	return this->getSize() / 1073741824.0;
}

long Folder::getPhysicalSize() const
{
	long totalBytes = 0;

	Array<File> files = this->getFiles();
	for(unsigned long i = 0; i < files.size(); i++)
	{
		totalBytes += files[i].getPhysicalSize();
	}

	Array<Folder> folders = this->getFolders();
	for(unsigned long i = 0; i < folders.size(); i++)
	{
		totalBytes += folders[i].getPhysicalSize();
	}

	#ifdef WIN32
		// TODO: fill out
	#endif
	#ifdef __linux__
		struct stat statBuffer;
		stat(currDir.cStr(), &statBuffer);
		totalBytes += statBuffer.st_size;
	#endif

	return totalBytes;
}
double Folder::getPhysicalSizeKB() const
{
	return this->getPhysicalSize() / 1024.0;
}
double Folder::getPhysicalSizeMB() const
{
	return this->getPhysicalSize() / 1048576.0;
}
double Folder::getPhysicalSizeGB() const
{
	return this->getPhysicalSize() / 1073741824.0;
}

Date Folder::getLastAccessed() const
{
	#ifdef WIN32
		// TODO: fill out
	#endif
	#ifdef __linux__
		struct stat statBuffer;
		stat(currDir.cStr(), &statBuffer);
	
		return Date(statBuffer.st_atime);
	#endif
}
Date Folder::getLastModified() const
{
	#ifdef WIN32
		// TODO: fill out
	#endif
	#ifdef __linux__
		struct stat statBuffer;
		stat(currDir.cStr(), &statBuffer);
	
		return Date(statBuffer.st_mtime);
	#endif
}

Folder& Folder::operator=(const Folder& rhs)
{
	this->currDir = rhs.currDir;
	return *this;
}
bool Folder::operator==(const Folder& rhs)
{
	return this->currDir == rhs.currDir;
}
bool Folder::operator!=(const Folder& rhs)
{
	return this->currDir != rhs.currDir;
}

String Folder::getCWD()
{
	return Folder().getPath();
}
void Folder::changeCWD(const String& newLocation)
{
	#ifdef WIN32
		// TODO: fill out
	#endif
	#ifdef __linux__
		if(chdir(newLocation.cStr()) != 0)
		{
			throw InvalidFolder(newLocation);
		}
	#endif
}
void Folder::changeCWD(char* newLocation)
{
	#ifdef WIN32
		// TODO: fill out
	#endif
	#ifdef __linux__
		if(chdir(newLocation) != 0)
		{
			throw InvalidFolder(newLocation);
		}
	#endif
}
