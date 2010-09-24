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
	KEY_ESCAPE, KEY_UP, KEY_DOWN, KEY_RIGHT, KEY_LEFT, KEY_PAGEUP, KEY_PAGEDOWN, KEY_W, KEY_A, KEY_S, KEY_D
};

class Key
{
public:
	Key(KeyType type);
	Key(const Key& orig);
	virtual ~Key();

	void keyPress();
	void keyDown();
	void keyUp();

	KeyType keyType();

	bool operator==(const Key& rhs);
	bool operator!=(const Key& rhs);
private:
	KeyType type;
};

#endif	/* _KEY_H */

