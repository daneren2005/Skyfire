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

#ifndef _SEARCH_STATE_PATH_H
#define	_SEARCH_STATE_PATH_H

#include "Array.h"
#include "Types.h"

class SearchState;
class SearchAction;

class SearchStatePath
{
public:
	SearchStatePath();
	SearchStatePath(SearchState* start);
	SearchStatePath(const SearchStatePath& orig, SearchAction* action);
	~SearchStatePath();
	
	SearchState* getStartState() const;
	SearchState* getEndState() const;
	double getCost() const;
	ulong getStates() const;
	ulong getActions() const;
	
	bool operator<(const SearchStatePath& rhs) const;
	bool operator>(const SearchStatePath& rhs) const;

	class Iterator;
	Iterator begin();
private:
	SearchState* startState;
	Array<SearchAction*> actions;
	SearchState* endState;
	double cost;
};

class SearchStatePath::Iterator
{
public:
	Iterator(SearchStatePath* orig);

	Iterator& operator++(int);
	bool operator !();

	SearchState* getCurrentState();
	SearchAction* getNextAction();
	void executeNextAction();
private:
	SearchStatePath* path;
	SearchState* current;
	ulong action;
};

#endif	/* SEARCHPATH_H */

