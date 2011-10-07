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

#ifndef _FOLDER_H
#define	_FOLDER_H

#include "File.h"
#include "Exceptions.h"

class Folder
{
public:
	Folder();
	Folder(const String& location);
	Folder(const Folder& orig);
	virtual ~Folder();

	String getPath() const;
	Folder getParentFolder() const;
	Folder getRootFolder() const;
	void changeLocation(const String& newLocation);

	bool canRead() const;
	bool canWrite() const;
	bool canExecute() const;
	int getPermissions() const;
	int getOwnerPermissions() const;
	int getGroupPermissions() const;
	int getOtherPermissions() const;
	// String getOwner() const;
	int getOwnerID() const;
	// String getGroup() const;
	int getGroupID() const;
	bool doesExist() const;

	// bool setPermissions(int mode);
	// bool setOwnerPermissions(int mode);
	// bool setGroupPermissions(int mode);
	// bool setOtherPermissions(int mode);
	// bool setOwner(int id);
	// bool setGroup(int id);

	Array<File> getFiles() const;
	Array<Folder> getFolders() const;

	// getFile returns a File object but does not create it if it doesnt exist
	File getFile(String name);
	// createFile returns a File object, creates if didnt exist
	File createFile(String name);
	Folder getSubFolder(String name);
	Folder createSubFolder(String name);

	long getSize() const;
	double getSizeKB() const;
	double getSizeMB() const;
	double getSizeGB() const;
	long getPhysicalSize() const;
	double getPhysicalSizeKB() const;
	double getPhysicalSizeMB() const;
	double getPhysicalSizeGB() const;

	Date getLastAccessed() const;
	Date getLastModified() const;

	Folder& operator=(const Folder& rhs);
	bool operator==(const Folder& rhs);
	bool operator!=(const Folder& rhs);

	static String getCWD();
	static void changeCWD(const String& newLocation);
	static void changeCWD(char* newLocation);
private:
	String currDir;

	static const long BUFFER_SIZE = 256;
	static const long BACKUP_BUFFER_SIZE = 4096;
};

class InvalidFolder : public Exception
{
public:
	InvalidFolder(String folderName)
	{
		this->folderName = folderName;
		this->msg = String("Exception: Invalid folder name: ") + folderName;
	}

	String folderName;
};


#endif	/* _FOLDER_H */

