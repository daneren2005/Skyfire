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

#include "SearchState.h"
#include "PriorityQueue.h"

SearchState::SearchState()
{
}

SearchState::~SearchState()
{
}

SearchStatePath SearchState::getPathToGoal(SearchState* goal)
{
	PriorityQueue<SearchStatePath> frontier;
	Array<SearchState*> expandedList;
	
	SearchStatePath start(this);
	frontier.insert(start);
	while(frontier.size() > 0)
	{
		SearchStatePath current = frontier.remove();
		SearchState* end = current.getEndState();
		
		// Check if the node has already been visited
		bool duplicate = false;
		for(ulong i = 0; i < expandedList.size(); i++)
		{
			if(end->equal(expandedList[i]))
			{
				duplicate = true;
				break;
			}
		}
		
		// Check if this path is the goal
		if(end->equal(goal))
		{
			// std::cout << "                 Generated " << count << " nodes" << std::endl;
			return current;
		}
		// Make sure not redoing work
		else if(!duplicate)
		{
			expandedList.insert(end);
			
			Array<SearchAction*> actions = end->getActions();
			for(ulong i = 0; i < actions.size(); i++)
			{
				SearchStatePath newPath(current, actions[i]);
				frontier.insert(newPath);
			}
		}
	}

	return SearchStatePath();
}
