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

#include "SharedLock.h"

SharedLock::SharedLock()
{
	this->buffer = new BUFFER();
}

SharedLock::SharedLock(const SharedLock& orig)
{
	this->buffer = orig.buffer;
}
SharedLock::~SharedLock()
{
	
}

void SharedLock::readLock()
{
	pthread_rwlock_rdlock(&buffer->lock);
	buffer->read = true;
}
void SharedLock::writeLock()
{
	pthread_rwlock_wrlock(&buffer->lock);
	buffer->write = true;
}

bool SharedLock::tryReadLock()
{
	if(pthread_rwlock_tryrdlock(&buffer->lock) == 0)
	{
		buffer->read = true;
		return true;
	}
	else
	{
		return false;
	}
}
bool SharedLock::tryWriteLock()
{
	if(pthread_rwlock_trywrlock(&buffer->lock) == 0)
	{
		buffer->write = true;
		return true;
	}
	else
	{
		return false;
	}
}

void SharedLock::unlock()
{
	pthread_rwlock_unlock(&buffer->lock);
	buffer->read = false;
	buffer->write = false;
}

bool SharedLock::isLocked()
{
	return buffer->read || buffer->write;
}
bool SharedLock::isReadLocked()
{
	return buffer->read;
}
bool SharedLock::isWriteLocked()
{
	return buffer->write;
}

SharedLock& SharedLock::operator=(const SharedLock& rhs)
{
	this->buffer = rhs.buffer;
	return *this;
}
bool SharedLock::operator==(const SharedLock& rhs)
{
	return this->buffer == rhs.buffer;
}
bool SharedLock::operator!=(const SharedLock& rhs)
{
	return this->buffer != rhs.buffer;
}
