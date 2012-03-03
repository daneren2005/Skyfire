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

#ifndef _KEY_H
#define	_KEY_H

#include "Function.h"

enum KeyType
{
	KEY_ESCAPE, KEY_UP, KEY_DOWN, KEY_RIGHT, KEY_LEFT, KEY_PAGEUP, KEY_PAGEDOWN, KEY_W, KEY_A, KEY_S, KEY_D,
	BUTTON_LEFT, BUTTON_MIDDLE, BUTTON_RIGHT, WHEEL_UP, WHEEL_DOWN,
	NULL_KEY
};

class Key
{
public:
	Key();
	Key(KeyType type);
	Key(const Key& orig);
	virtual ~Key();

	void keyDown(int x = 0, int y = 0);
	void keyUp(int x = 0, int y = 0);
	bool keyPressed();

	KeyType keyType();

	bool operator==(const Key& rhs);
	bool operator!=(const Key& rhs);

	void update(double interval, int x = 0, int y = 0);

	void setKeyPressEventHandler(void*(*eventHandler)(void* args), void* args);
	void setKeyDownEventHandler(Function<void, double> eventHandler);
	void setMousePressEventHandler(Function<void, int, int> eventHandler);
	void setMouseDownEventHandler(Function<void, double, int, int> eventHandler);
private:
	KeyType type;
	bool pressed;

	// Function<void, void> keyPressHandler;
	Function<void, double> keyDownHandler;
	Function<void, int, int> mousePressHandler;
	Function<void, double, int, int> mouseDownHandler;
	
	void*(*keyPressHandler)(void* args);
	void* keyPressArgs;
	/*void*(*keyDownHandler)(void* args, double interval);
	void* keyDownArgs;
	void*(*mousePressHandler)(void* args, int x, int y);
	void* mousePressArgs;
	void*(*mouseDownHandler)(void* args, double interval, int x, int y);
	void* mouseDownArgs;*/
};

#endif	/* _KEY_H */

