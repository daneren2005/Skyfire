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

	void keyDown();
	void keyUp();
	bool keyPressed();

	KeyType keyType();

	bool operator==(const Key& rhs);
	bool operator!=(const Key& rhs);

	void setEventHandler(void*(*eventHandler)());
private:
	KeyType type;
	bool pressed;
	void*(*eventHandler)();
};

#endif	/* _KEY_H */

