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

	bool moveLeft;
	bool moveRight;
	bool moveUp;
	bool moveDown;
	bool moveIn;
	bool moveOut;

	bool rotateLeft;
	bool rotateRight;
	bool rotateUp;
	bool rotateDown;
private:
	int mouseX;
	int mouseY;
	Map<KeyType, Key> keys;
};

#endif	/* _INPUT_H */

