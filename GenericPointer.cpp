#include "GenericPointer.h"

GenericPointer::GenericPointer()
{
	this->value = 0x0;
}
GenericPointer::GenericPointer(const GenericPointer& orig)
{
	this->value = orig.value;
}

GenericPointer& GenericPointer::operator=(GenericPointer& rhs)
{
	if(this == &rhs)
		return *this;

	this->value = rhs.value;
	return *this;
}

bool GenericPointer::operator==(const GenericPointer& rhs)
{
	return this->value == rhs.value;
}

bool GenericPointer::operator!=(const GenericPointer& rhs)
{
	return this->value != rhs.value;
}

void* GenericPointer::operator*()
{
	return value;
}
