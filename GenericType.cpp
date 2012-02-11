#include "GenericType.h"
#include "Console.h"

GenericType::GenericType()
{
	value = 0x0;
}
GenericType::GenericType(const GenericType& orig)
{
	if(orig.value == 0x0)
		this->value = 0x0;
	else
		this->value = orig.value->copy();
}
GenericType::~GenericType()
{
	if(this->value != 0x0)
		delete value;
}

GenericType& GenericType::operator=(const GenericType& rhs)
{
	if(this->value != 0x0)
		delete this->value;

	if(rhs.value == 0x0)
		this->value = 0x0;
	else
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

