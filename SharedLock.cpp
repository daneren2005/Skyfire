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
	this->buffer->readers = 0;
	this->buffer->writing = false;
	this->buffer->readWaiting = 0;
	this->buffer->writeWaiting = 0;
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
	buffer->lock.lock();
	if(buffer->writing || buffer->writeWaiting)
	{
		buffer->readWaiting++;
		while(buffer->writing || buffer->writeWaiting)
		{
			buffer->read.wait(buffer->lock);
		}
		buffer->readWaiting--;
	}

	buffer->readers++;
	buffer->lock.unlock();
}
void SharedLock::writeLock()
{
	buffer->lock.lock();
	if(buffer->readers > 0 || buffer->writing)
	{
		buffer->writeWaiting++;
		while(buffer->readers > 0 || buffer->writing)
		{
			buffer->write.wait(buffer->lock);
		}
		buffer->writeWaiting--;
	}

	buffer->writing = true;
	buffer->lock.unlock();
}

bool SharedLock::tryReadLock()
{
	bool value;

	buffer->lock.lock();
	if(buffer->writing || buffer->writeWaiting)
	{
		value = false;
	}
	else
	{
		buffer->readers++;
		value = true;
	}

	buffer->lock.unlock();
	return value;
}
bool SharedLock::tryWriteLock()
{
	bool value;

	buffer->lock.lock();
	if(buffer->readers > 0 || buffer->writing)
	{
		value = false;
	}
	else
	{
		buffer->writing = true;
		value = true;
	}

	buffer->lock.unlock();
	return value;
}

void SharedLock::unlock()
{
	buffer->lock.lock();

	// Unlocking a writer
	if(buffer->writing)
	{
		buffer->writing = false;
		if(buffer->writeWaiting > 0)
		{
			buffer->write.signal();
		}
		else if(buffer->readWaiting > 0)
		{
			buffer->read.broadcast();
		}
	}
	// Unlocking a reader
	else if(buffer->readers > 0)
	{
		buffer->readers--;
		if(buffer->readers <= 0 && buffer->writeWaiting > 0)
		{
			buffer->write.signal();
		}
	}

	buffer->lock.unlock();
}

bool SharedLock::isLocked()
{
	buffer->lock.lock();
	bool value = buffer->writing || (buffer->readers > 0);
	buffer->lock.unlock();
	
	return value;
}
bool SharedLock::isWriteLocked()
{
	buffer->lock.lock();
	bool value = buffer->writing;
	buffer->lock.unlock();
	
	return value;
}
long SharedLock::readLocks()
{
	buffer->lock.lock();
	long value = buffer->readers;
	buffer->lock.unlock();
	
	return value;
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

