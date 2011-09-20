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

#include "Condition.h"

Condition::Condition()
{
	this->buffer = new BUFFER();
}
Condition::Condition(Condition& orig)
{
	this->buffer = orig.buffer;
}
Condition::~Condition()
{
	
}

void Condition::wait(Lock lock)
{
	pthread_cond_wait(&buffer->condition, &lock.buffer->lock);
}
void Condition::signal()
{
	pthread_cond_signal(&buffer->condition);
}
void Condition::broadcast()
{
	pthread_cond_signal(&buffer->condition);
}

Condition& Condition::operator=(Condition& rhs)
{
	this->buffer = rhs.buffer;
	return *this;
}
bool Condition::operator==(Condition& rhs)
{
	return this->buffer == rhs.buffer;
}
bool Condition::operator!=(Condition& rhs)
{
	return this->buffer != rhs.buffer;
}
