/* 
 * File:   Map.h
 * Author: scott
 *
 * Created on October 20, 2010, 1:32 PM
 */

#ifndef _MAP_H
#define	_MAP_H

#include <iostream>

template <class Key, class T>
class Map
{
public:
	Map();
	Map(const Map& orig);
	virtual ~Map();

	T& operator[](Key key);
	const T& operator[](Key key) const;

	void insert(Key access, T value);
	T get(Key key);
private:
	class Node
	{
	public:
		Node(Key key, T value)
		{
			this->key = key;
			this->value = value;
			this->prev = NULL;
			this->next = NULL;
		}

		Key key;
		T value;

		Node* prev;
		Node* next;
	};

	Node* head;
	Node* tail;
	long count;
};

template <class Key, class T>
Map<Key, T>::Map()
{
	head = NULL;
	tail = NULL;
	count = 0;
}

template <class Key, class T>
Map<Key, T>::Map(const Map& orig)
{
	// TODO: fill in map copy constructor
}

template <class Key, class T>
Map<Key, T>::~Map()
{
	// TODO: fill in map deconstructor
}

template <class Key, class T>
T& Map<Key, T>::operator [](Key key)
{
	// Write
	if(head == NULL)
	{
		T empty;
		this->head = new Node(key, empty);
		this->tail = this->head;
		return empty;
	}
	else
	{
		for(Node* node = head; node != NULL; node = node->next)
		{
			if(key == node->key)
			{
				return node->value;
			}
		}
	}

	T empty;
	Node* node = new Node(key, empty);
	this->tail->next = node;
	node->prev = this->tail;
	this->tail = node;
	return empty;
}

template <class Key, class T>
const T& Map<Key, T>::operator[](Key key) const
{
	// Read
	if(head == NULL)
	{
		return NULL;
	}
	else
	{
		for(Node* node = head; node != NULL; node = node->next)
		{
			if(key == node->key)
			{
				return node->value;
			}
		}
	}

	return NULL;
}

template <class Key, class T>
void Map<Key, T>::insert(Key key, T value)
{
	Node* node = new Node(key, value);
	if(head == NULL)
	{
		this->head = node;
		this->tail = node;
	}
	else
	{
		this->tail->next = node;
		node->prev = this->tail;
		this->tail = node;
	}
}

template <class Key, class T>
T Map<Key, T>::get(Key key)
{
	if(head == NULL)
	{
		return NULL;
	}
	else
	{
		for(Node* node = head; node != NULL; node = node->next)
		{
			if(key == node->key)
			{
				return node->value;
			}
		}
	}

	return NULL;
}

#endif	/* _MAP_H */

