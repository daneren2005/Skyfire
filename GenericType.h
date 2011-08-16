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

#ifndef _GENERIC_TYPE_H
#define	_GENERIC_TYPE_H

class GenericType
{
public:
	GenericType();
	GenericType(const GenericType& orig);
	template <class T>
	GenericType(T orig);
	~GenericType();

	GenericType& operator=(const GenericType& rhs);
	template <class T>
	GenericType& operator=(T rhs);

	bool operator==(const GenericType& rhs);
	template <class T>
	bool operator==(T rhs);
	bool operator!=(const GenericType& rhs);
	template <class T>
	bool operator!=(T rhs);

	template <class T>
	operator T() const;
	template <class T>
	T cast() const;
private:
	class ValueBase;
	template <class T>
	class Value;

	ValueBase* value;
};

template <class T>
GenericType::GenericType(T orig)
{
	this->value = new Value<T>(orig);
}
template <class T>
GenericType& GenericType::operator=(T rhs)
{
	if(this->value != 0x0)
		delete this->value;

	this->value = new Value<T>(rhs);
	return *this;
}

template <class T>
bool GenericType::operator==(T rhs)
{
	return ((Value<T>*)value)->value == rhs;
}
template <class T>
bool GenericType::operator!=(T rhs)
{
	return ((Value<T>*)value)->value != rhs;
}

// TODO: fix cast operator
template <class T>
GenericType::operator T() const
{
	return ((Value<T>*)value)->cast();
}

template <class T>
T GenericType::cast() const
{
	return ((Value<T>*)value)->cast();
}

//////////////////////////////////////////////////////////////////
/////////////////////////// Value ////////////////////////////////
//////////////////////////////////////////////////////////////////

class GenericType::ValueBase
{
public:
	virtual ~ValueBase() {}
	virtual ValueBase* copy() const = 0;

	virtual bool isEqual(ValueBase* rhs) const = 0;
};

template <class T>
class GenericType::Value : public ValueBase
{
public:
	Value(T value)
	{
		this->value = value;
	}

	ValueBase* copy() const
	{
		return new Value(value);
	}

	T cast() const
	{
		return value;
	}

	// TODO: seg faults if incorrect type comparison
	bool isEqual(ValueBase* rhs) const
	{
		try
		{
			return this->value == ((Value<T>*)rhs)->value;
		}
		catch(...)
		{
			return false;
		}
	}

	T value;
};

#endif
