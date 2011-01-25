/* 
 * File:   Keyboard.h
 * Author: scott
 *
 * Created on July 14, 2010, 6:16 PM
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

	void setMousePressEventHandler(KeyType key, void*(*eventHandler)(void* args, int x, int y), void* args);
	void setMouseDownEventHandler(KeyType key, void*(*eventHandler)(void* args, double interval, int x, int y), void* args);
	void setMouseMoveEventHandler(void*(*eventHandler)(void* args, int x, int y), void* args);
	void setKeyPressEventHandler(KeyType key, void*(*eventHandler)(void* args), void* args);
	void setKeyDownEventHandler(KeyType key, void*(*eventHandler)(void* args, double interval), void* args);

	void update(double interval);
private:
	int mouseX;
	int mouseY;
	void* mouseArgs;
	void*(*mouseHandler)(void* args, int x, int y);

	Map<KeyType, Key*> keys;
};

#endif	/* _INPUT_H */

