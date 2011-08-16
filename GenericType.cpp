#include "GenericType.h"

GenericType::GenericType()
{
	value = 0x0;
}
GenericType::GenericType(const GenericType& orig)
{
	this->value = orig.value->copy();
}
GenericType::~GenericType()
{
	delete value;
}

GenericType& GenericType::operator=(const GenericType& rhs)
{
	if(this->value != 0x0)
		delete this->value;

	this->value = rhs.value->copy();
	return *this;
}

bool GenericType::operator==(const GenericType& rhs)
{
	return value->isEqual(rhs.value);
}
bool GenericType::operator!=(const GenericType& rhs)
{
	return !value->isEqual(rhs.value);
}

