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

#ifndef _ITERATOR_H_
#define	_ITERATOR_H_

template <class Value>
class IteratorBase
{
public:
	virtual ~IteratorBase() {}

	virtual Value value() = 0;

	virtual bool end() = 0;
	virtual void next() = 0;

	inline bool operator !()
	{
		return this->end();
	}
	inline void operator ++(int)
	{
		this->next();
	}
};

#endif
