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

#include "FunctionCall.h"

FunctionCall::FunctionCall()
{
	this->container = nullptr;
}
FunctionCall::FunctionCall(Function<void> function)
{
	this->container = new FunctionCall::ContainerBase(function);
}
FunctionCall::FunctionCall(const FunctionCall& orig)
{
	this->container = orig.container;
}
FunctionCall::~FunctionCall()
{

}

void FunctionCall::execute()
{
	container->execute();
}

FunctionCall& FunctionCall::operator =(const FunctionCall& rhs)
{
	this->container = rhs.container;
	return *this;
}
bool FunctionCall::operator ==(const FunctionCall& rhs)
{
	return this->container == rhs.container;
}
bool FunctionCall::operator !=(const FunctionCall& rhs)
{
	return this->container != rhs.container;
}
