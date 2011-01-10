/* 
 * File:   Map.h
 * Author: scott
 *
 * Created on October 20, 2010, 1:32 PM
 */

#ifndef _MAP_H
#define	_MAP_H

#include "Exceptions.h"
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
	T search(const Key& key);
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
	this->head = NULL;
	this->tail = NULL;
	Node* current = NULL;
	for(Node* node = orig.head; node != NULL; node = node->next)
	{
		if(this->head == NULL)
		{
			this->head = new Node(node->key, node->value);
			current = this->head;
		}
		else
		{
			current->next = new Node(node->key, node->value);
			current = current->next;
		}
	}
	this->tail = current;
	this->count = orig.count;
}

template <class Key, class T>
Map<Key, T>::~Map()
{
	// TODO: fix buggy destructor
	/*while(this->head != NULL)
	{
		Node* toDelete = head;
		this->head = toDelete->next;
		delete toDelete;
	}*/
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
		throw OutOfRange();
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

	throw OutOfRange();
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
T Map<Key, T>::search(const Key& key)
{
	if(head == NULL)
	{
		throw OutOfRange();
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

	throw OutOfRange();
}

#endif	/* _MAP_H */

