/* 
 * File:   Key.h
 * Author: scott
 *
 * Created on July 20, 2010, 8:06 PM
 */

#ifndef _KEY_H
#define	_KEY_H

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
	void setKeyDownEventHandler(void*(*eventHandler)(void* args, double interval), void* args);
	void setMousePressEventHandler(void*(*eventHandler)(void* args, int x, int y), void* args);
	void setMouseDownEventHandler(void*(*eventHandler)(void* args, double interval, int x, int y), void* args);
private:
	KeyType type;
	bool pressed;

	void*(*keyPressHandler)(void* args);
	void* keyPressArgs;
	void*(*keyDownHandler)(void* args, double interval);
	void* keyDownArgs;
	void*(*mousePressHandler)(void* args, int x, int y);
	void* mousePressArgs;
	void*(*mouseDownHandler)(void* args, double interval, int x, int y);
	void* mouseDownArgs;
};

#endif	/* _KEY_H */

