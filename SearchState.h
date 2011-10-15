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

#ifndef _SEARCH_STATE_H
#define	_SEARCH_STATE_H

#include "SearchStatePath.h"
#include "Array.h"

class SearchAction;

class SearchState
{
public:
	SearchState();
	virtual ~SearchState();
	
	SearchStatePath getPathToGoal(SearchState* goal);
	
	virtual double getHeuristic() = 0;
	virtual Array<SearchAction*> getActions() = 0;
	virtual bool equal(SearchState* rhs) = 0;
};

class SearchAction
{
public:
	SearchAction() {}
	virtual ~SearchAction() {}

	virtual void execute() = 0; 
	virtual double getCost() = 0;
	virtual SearchState* getResultState()
	{
		return resultState;
	}
protected:
	SearchState* resultState;
};

#endif	/* SEARCHSTATE_H */

