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

#include "SearchStatePath.h"
#include "SearchState.h"

SearchStatePath::SearchStatePath()
{
	this->startState = 0x0;
	this->endState = 0x0;
	this->cost = 0;
}
SearchStatePath::SearchStatePath(SearchState* start)
{
	this->startState = start;
	this->endState = start;
	this->cost = 0;
}
SearchStatePath::SearchStatePath(const SearchStatePath& orig, SearchAction* action)
{
	this->startState = orig.startState;
	this->actions = orig.actions;
	this->actions.insert(action);
	this->cost = orig.cost + action->getCost();
	this->endState = action->getResultState();
}

SearchStatePath::~SearchStatePath()
{
}

SearchState* SearchStatePath::getStartState() const
{
	return startState;
}
SearchState* SearchStatePath::getEndState() const
{
	return endState;
}
double SearchStatePath::getCost() const
{
	return cost;
}
ulong SearchStatePath::getStates() const
{
	return (startState != 0x0) ? actions.size() + 1 : 0;
}
ulong SearchStatePath::getActions() const
{
	return actions.size();
}

bool SearchStatePath::operator<(const SearchStatePath& rhs) const
{
	return this->cost + this->endState->getHeuristic() < rhs.cost + rhs.endState->getHeuristic();
}

bool SearchStatePath::operator>(const SearchStatePath& rhs) const
{
	return this->cost + this->endState->getHeuristic() > rhs.cost + rhs.endState->getHeuristic();
}

SearchStatePath::Iterator SearchStatePath::begin()
{
	return Iterator(this);
}


SearchStatePath::Iterator::Iterator(SearchStatePath* orig)
{
	this->path = orig;
	this->current = orig->startState;
	this->action = 0;
}

SearchStatePath::Iterator& SearchStatePath::Iterator::operator++(int)
{
	if(action >= path->actions.size())
	{
		current = 0x0;
	}
	else
	{
		current = path->actions[action]->getResultState();
		action++;
	}

	return *this;
}
bool SearchStatePath::Iterator::operator !()
{
	return current != 0x0;
}

SearchState* SearchStatePath::Iterator::getCurrentState()
{
	return current;
}
SearchAction* SearchStatePath::Iterator::getNextAction()
{
	return (action >= path->actions.size()) ? 0x0 : path->actions[action];
}
void SearchStatePath::Iterator::executeNextAction()
{
	path->actions[action]->execute();
}
