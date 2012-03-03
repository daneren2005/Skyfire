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

#ifndef _INPUT_H
#define	_INPUT_H

#ifdef __linux__
	#include <SDL/SDL.h>
#endif

#include "List.h"
#include "Map.h"
#include "Key.h"

class Input
{
public:
	Input();
	Input(const Input& orig);
	virtual ~Input();

	void keyDown(KeyType key);
	void keyUp(KeyType key);
	void mouseMove(int x, int y);
	bool keyPressed(KeyType key);

	int mouseLocationX();
	int mouseLocationY();

	void setMousePressEventHandler(KeyType key, Function<void, int, int> eventHandler);
	void setMouseDownEventHandler(KeyType key, Function<void, double, int, int> eventHandler);
	void setMouseMoveEventHandler(Function<void, int, int> eventHandler);
	void setKeyPressEventHandler(KeyType key, void*(*eventHandler)(void* args), void* args);
	void setKeyDownEventHandler(KeyType key, Function<void, double> eventHandler);

	void update(double interval);
private:
	int mouseX;
	int mouseY;
	Function<void, int, int> mouseHandler;
	
	Map<Key*, KeyType> keys;
};

#endif	/* _INPUT_H */

