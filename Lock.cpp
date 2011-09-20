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

#include "Lock.h"

Lock::Lock()
{
	this->buffer = new BUFFER();
}

Lock::Lock(const Lock& orig)
{
	this->buffer = orig.buffer;
}
Lock::~Lock()
{

}

void Lock::lock()
{
	pthread_mutex_lock(&buffer->lock);
	buffer->locked = false;
}
bool Lock::tryLock()
{
	if(pthread_mutex_trylock(&buffer->lock) == 0)
	{
		buffer->locked = true;
		return true;
	}
	else
	{
		return false;
	}
}
void Lock::unlock()
{
	buffer->locked = false;
	pthread_mutex_unlock(&buffer->lock);
}
bool Lock::isLocked()
{
	return buffer->locked;
}

Lock& Lock::operator=(const Lock& rhs)
{
	this->buffer = rhs.buffer;
	return *this;
}
bool Lock::operator==(const Lock& rhs)
{
	return this->buffer == rhs.buffer;
}
bool Lock::operator!=(const Lock& rhs)
{
	return this->buffer == rhs.buffer;
}

