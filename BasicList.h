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

// Fixed destructor double delete bug

#ifndef _BASIC_LIST_H
#define	_BASIC_LIST_H

// For use of NULL
#include <iostream>

// ------------------------ BasicList Class
template <class T>
class BasicList
{
public:
	BasicList();
	BasicList(const BasicList<T>& list);
	~BasicList();

	T front();
	T back();
	bool empty();
	long size();

	void pushFront(const T& value);
	void pushBack(const T& value);
	T popFront();
	T popBack();
	void remove(T value);
	
	BasicList& operator=(const BasicList& orig);
	
	class Iterator;
	class ReverseIterator;

	Iterator begin();
	ReverseIterator reverseBegin();
private:
	class Node
	{
	public:
		Node(const T& value)
		{
			this->value = value;
			this->next = NULL;
			this->prev = NULL;
		}
		~Node()
		{
			
		}

		T value;
		Node* next;
		Node* prev;

	};

	// Double sided
	Node* head;
	Node* tail;

	// Running size counter
	long count;
};

template <class T>
BasicList<T>::BasicList()
{
	count = 0;

	head = NULL;
	tail = NULL;
}
template <class T>
BasicList<T>::BasicList(const BasicList<T>& list)
{
	Node* current = NULL;
	for(Node* node = list.head; node != NULL; node = node->next)
	{

		// If its the first run
		if(this->head == NULL)
		{
			this->head = new Node(node->value);
			current = head;
		}
		// Otherwise make the next
		else
		{
			current->next = new Node(node->value);
			current->next->prev = current;
			current = current->next;
		}
	}

	if(current == NULL)
	{
		this->head = NULL;
		this->tail = NULL;
	}
	else
	{
		this->tail->node = current;
	}
}

template <class T>
BasicList<T>::~BasicList()
{
	while(this->head != NULL)
	{
		Node* toDelete = this->head;
		this->head = toDelete->next;
		delete toDelete;
	}
}

template <class T>
T BasicList<T>::front()
{
	if(this->head == NULL)
	{
		return NULL;
	}
	else
	{
		T value = this->head->value;
		return value;
	}
}

template <class T>
T BasicList<T>::back()
{
	if(this->tail == NULL)
	{
		return NULL;
	}
	else
	{
		T value = this->tail->value;
		return value;
	}
}

template <class T>
bool BasicList<T>::empty()
{
	if(this->head == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template <class T>
long BasicList<T>::size()
{
	// Single operation, shouldn't need a lock
	long value = this->count;
	return value;
}

template <class T>
void BasicList<T>::pushFront(const T& value)
{
	if(this->head == NULL)
	{
		// Create new node and make it head and tail
		this->head = new Node(value);
		this->tail = head;
	}
	else
	{
		// Make new node, set it as new head
		Node* newNode = new Node(value);
		newNode->next = this->head;
		this->head->prev = newNode;
		this->head = newNode;
	}

	// Increment counter
	count++;
}

template <class T>
void BasicList<T>::pushBack(const T& value)
{
	if(head == NULL)
	{
		this->head = new Node(value);
		this->tail = head;
	}
	else
	{
		Node* newNode = new Node(value);
		this->tail->next = newNode;
		newNode->prev = this->tail;
		this->tail = newNode;
	}

	count++;
}

template <class T>
T BasicList<T>::popFront()
{
	if(this->head == NULL)
	{
		return NULL;
	}
	else if(head == tail)
	{
		// lock node in case a iterator is currently on it
		// set head and tail to null then unlock
		Node* toDelete = this->head;
		this->head = NULL;
		this->tail = NULL;

		// increment counter
		count--;

		// delete old head node and return its value
		T value = toDelete->value;
		delete toDelete;
		return value;
	}
	else
	{
		// Lock head and next node, going to be changed

		// Set next head and release headlock
		Node* toDelete = this->head;
		this->head = toDelete->next;
		this->head->prev = NULL;

		// decrement counter
		count--;

		// delete old head node and return its value
		T value = toDelete->value;
		delete toDelete;
		return value;
	}
}

template <class T>
T BasicList<T>::popBack()
{
	if(tail == NULL)
	{
		return NULL;
	}
	else if(head == tail)
	{
		// lock node, fix pointers, unlock
		Node* toDelete = this->tail;
		this->head = NULL;
		this->tail = NULL;

		// decrement counter
		count--;

		// delete node and return value
		T value = toDelete->value;
		delete toDelete;
		return value;

	}
	else
	{
		// Lock tail nodes

		// set next tail and release headlock
		Node* toDelete = this->tail;
		this->tail = toDelete->prev;
		this->tail->next = NULL;

		// decrement counter
		count--;

		// delete node and return value
		T value = toDelete->value;
		delete toDelete;
		return value;
	}
}

template <class T>
void BasicList<T>::remove(T value)
{
	// Lock head since starting there
	Node* toDelete = NULL;
	Node* current = this->head;
	// Make sure not empty
	if(current == NULL)
	{
		return;
	}

	// Check head, delete if it is head
	if(current->value == value)
	{
		// Delete head then and exit
		toDelete = current;
		if(head->next == NULL)
		{
			delete this->head;
			this->head = NULL;
			this->tail = NULL;
		}
		else
		{
			this->head = toDelete->next;
			delete toDelete;
			this->head->prev = NULL;
		}

	}
	// Otherwise search for and destroy the node
	else
	{

		// Get the node that is to be deleted
		while(current->next != NULL)
		{
			current = current->next;
			if(current->value == value)
			{
				toDelete = current;
				break;
			}
		}

		if(toDelete == NULL)
		{
			return;
		}
		else
		{
			toDelete->prev->next = toDelete->next;
			toDelete->next->prev = toDelete->prev;
			delete toDelete;
		}
	}

	count--;
}

template <class T>
BasicList<T>& BasicList<T>::operator=(const BasicList& orig)
{	
	// Delete old stuff
	while(this->head != NULL)
	{
		Node* toDelete = this->head;
		this->head = toDelete->next;
		delete toDelete;
	}
	
	// Copy new stuff
	Node* current = NULL;
	for(Node* node = orig.head; node != NULL; node = node->next)
	{
		// If its the first run
		if(this->head == NULL)
		{
			this->head = new Node(node->value);
			current = head;
		}
		// Otherwise make the next
		else
		{
			current->next = new Node(node->value);
			current->next->prev = current;
			current = current->next;
		}
	}

	if(current == NULL)
	{
		this->head = NULL;
		this->tail = NULL;
	}
	else
	{
		this->tail = current;
	}
}

template <class T>
class BasicList<T>::Iterator
{
public:
	Iterator(BasicList<T>* list)
	{
		this->current = list->head;
	}

	T value()
	{
		if(current == NULL)
			return NULL;
		else
			return this->current->value;
	}

	T remove()
	{
		typename BasicList<T>::Node* toDelete = current;
		current->prev->next = current->next;
		current->next->prev = current->prev;
		current = current->next;

		delete toDelete;
	}

	// Operator Overloading
	bool operator !()
	{
		if(this->current == NULL)
			return false;
		else
			return true;
	}
	void operator ++(int)
	{
		this->current = this->current->next;
	}
private:
	typename BasicList<T>::Node* current;
};

template <class T>
class BasicList<T>::ReverseIterator
{
public:
	ReverseIterator(BasicList<T>* list)
	{
		this->current = list->tail;
	}

	T value()
	{
		if(current == NULL)
			return NULL;
		else
			return this->current->value;
	}

	T remove()
	{
		typename BasicList<T>::Node* toDelete = current;
		current->prev->next = current->next;
		current->next->prev = current->prev;
		current = current->prev;

		delete toDelete;
	}

	// Operator Overloading
	bool operator !()
	{
		if(this->current == NULL)
			return false;
		else
			return true;
	}
	void operator ++(int)
	{
		this->current = this->current->prev;
	}
private:
	typename BasicList<T>::Node* current;
};

template <class T>
typename BasicList<T>::Iterator BasicList<T>::begin()
{
	return Iterator(this);
}

template <class T>
typename BasicList<T>::ReverseIterator BasicList<T>::reverseBegin()
{
	return ReverseIterator(this);
}

#endif	/* _LIST_H */