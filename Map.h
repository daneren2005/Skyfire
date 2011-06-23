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

#ifndef _MAP_H
#define	_MAP_H

#include "Exceptions.h"
#include <iostream>

template <class Key, class T>
class Map
{
private:
	class Node
	{
	public:
		Node(const Key& key, const T& value)
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
public:
	Map();
	Map(const Map& orig);
	virtual ~Map();

	T& operator[](const Key& key);
	const T& operator[](const Key& key) const;

	void insert(const Key& access, const T& value);
	T search(const Key& key);

	class Iterator
	{
	private:
		typename Map<Key, T>::Node* current;
	public:
		Iterator(Map<Key, T>* map)
		{
			this->current = map->head;
		}

		T value()
		{
			if(current == NULL)
			{
				return NULL;
			}
			else
			{
				return this->current->value;
			}
		}

		// Operator Overloading
		bool operator !()
		{
			if(this->current == NULL)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		void operator ++()
		{
			if(current != NULL)
			{
				this->current = this->current->next;
			}
		}
		void operator ++(int)
		{
			if(current != NULL)
			{
				this->current = this->current->next;
			}
		}
	};

	Iterator begin()
	{
		return Iterator(this);
	}
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
T& Map<Key, T>::operator [](const Key& key)
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
const T& Map<Key, T>::operator[](const Key& key) const
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
void Map<Key, T>::insert(const Key& key, const T& value)
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

