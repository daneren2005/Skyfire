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

#ifndef _TUPLE_H__
#define	_TUPLE_H__

#include "Types.h"

template <class... T>
class Tuple;

template <ulong I, class... T>
class TupleElement;

template <ulong I, class H, class... T>
class TupleElement<I, Tuple<H, T...> > : private TupleElement<I - 1, Tuple<T...> >
{
public:
	TupleElement(Tuple<H, T...>& tuple) : TupleElement<I - 1, Tuple<T...> >(tuple.next()) {	}
	typedef typename TupleElement<I - 1, Tuple<T...> >::type type;
	using TupleElement<I - 1, Tuple<T...> >::value;
};

template <class H, class... T>
class TupleElement<0, Tuple<H, T...> >
{
public:
	TupleElement(Tuple<H, T...>& tuple) {	this->value = &tuple.front();	}
	typedef H type;
	H* value;
};

template <class H, class... T>
class Tuple<H, T...> : private Tuple<T...>
{
public:
	Tuple();
	Tuple(const H& h, const T&... t);

	template <ulong I>
	typename TupleElement<I, Tuple<H, T...> >::type& get();
	template <ulong I>
	const typename TupleElement<I, Tuple<H, T...> >::type& get() const;

	typedef H frontType;
	H& front();
	const H& front() const;
	Tuple<T...>& next();
	const Tuple<T...>& next() const;

	ulong size();

	template <class H2, class... T2>
	Tuple<H, T...>& operator =(const Tuple<H2, T2...>& tuple);
	template <class H2, class... T2>
	bool operator ==(const Tuple<H2, T2...>& tuple);
	template <class H2, class... T2>
	bool operator !=(const Tuple<H2, T2...>& tuple);
	template <class H2, class... T2>
	bool operator <(const Tuple<H2, T2...>& tuple);
	template <class H2, class... T2>
	bool operator <=(const Tuple<H2, T2...>& tuple);
	template <class H2, class... T2>
	bool operator >(const Tuple<H2, T2...>& tuple);
	template <class H2, class... T2>
	bool operator >=(const Tuple<H2, T2...>& tuple);

	static const ulong length = Tuple<T...>::length + 1;
protected:
	H value;
};

template <>
class Tuple<>
{
public:
	Tuple<> operator=(const Tuple<>&) { return *this; }
	bool operator ==(const Tuple<>&) { return true; }
	bool operator <(const Tuple<>&) { return false; }
	bool operator >(const Tuple<>&) { return false; }
protected:
	static const ulong length = 0;
};

//////////////////// Functions ////////////////////////

template <class H, class... T>
Tuple<H, T...>::Tuple()
{
	
}
template <class H, class... T>
Tuple<H, T...>::Tuple(const H& h, const T&... t) : Tuple<T...>(t...)
{
	this->value = h;
}

template <class H, class... T>
template <ulong I>
typename TupleElement<I, Tuple<H, T...> >::type& Tuple<H, T...>::get()
{
	return *TupleElement<I, Tuple<H, T...> >(*this).value;
}
template <class H, class... T>
template <ulong I>
const typename TupleElement<I, Tuple<H, T...> >::type& Tuple<H, T...>::get() const
{
	return *TupleElement<I, Tuple<H, T...> >(*this).value;
}

template <class H, class... T>
H& Tuple<H, T...>::front()
{
	return this->value;
}
template <class H, class... T>
const H& Tuple<H, T...>::front() const
{
	return this->value;
}
template <class H, class... T>
Tuple<T...>& Tuple<H, T...>::next()
{
	return *this;
}
template <class H, class... T>
const Tuple<T...>& Tuple<H, T...>::next() const
{
	return *this;
}

template <class H, class... T>
ulong Tuple<H, T...>::size()
{
	return Tuple<H, T...>::length;
}

template <class H, class... T>
template <class H2, class... T2>
Tuple<H, T...>& Tuple<H, T...>::operator =(const Tuple<H2, T2...>& tuple)
{
	this->value = tuple.value;
	this->next() = tuple.next();
	return *this;
}

template <class H, class... T>
template <class H2, class... T2>
bool Tuple<H, T...>::operator ==(const Tuple<H2, T2...>& tuple)
{
	return this->value == tuple.value && this->next() == tuple.next();
}
template <class H, class... T>
template <class H2, class... T2>
bool Tuple<H, T...>::operator !=(const Tuple<H2, T2...>& tuple)
{
	return !(*this == tuple);
}
template <class H, class... T>
template <class H2, class... T2>
bool Tuple<H, T...>::operator <(const Tuple<H2, T2...>& tuple)
{
	return this->value < tuple.value || (!(this->value < tuple.value) && this->next() < tuple.next());
}
template <class H, class... T>
template <class H2, class... T2>
bool Tuple<H, T...>::operator <=(const Tuple<H2, T2...>& tuple)
{
	return !(*this > tuple);
}
template <class H, class... T>
template <class H2, class... T2>
bool Tuple<H, T...>::operator >(const Tuple<H2, T2...>& tuple)
{
	return this->value > tuple.value || (!(this->value > tuple.value) && this->next() > tuple.next());
}
template <class H, class... T>
template <class H2, class... T2>
bool Tuple<H, T...>::operator >=(const Tuple<H2, T2...>& tuple)
{
	return !(*this < tuple);
}

#endif