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

#ifndef _LIST_H
#define	_LIST_H

// For use of NULL
#include <iostream>
#include <pthread.h>

// Pre declare
template <class T>
class Node;

template <class T>
class Iterator;

// ------------------------ List Class
template <class T>
class List
{
public:
	List();
	List(const List<T>& list);
	~List();

	T front();
	T back();
	bool empty();
	long size();

	void pushFront(const T& value);
	void pushBack(const T& value);
	T popFront();
	T popBack();
	void remove(T value);
	
	class Iterator;
	class WriteIterator;
	
	Iterator begin();
	WriteIterator beginWrite();
private:
	class Node
	{
	public:
		Node(const T& value)
		{
			this->value = value;
			this->next = NULL;
			this->prev = NULL;

			pthread_rwlock_init(&this->lock, NULL);
		}
		~Node()
		{
			pthread_rwlock_destroy(&this->lock);
		}

		T value;
		Node* next;
		Node* prev;

		pthread_rwlock_t lock;
	};

	// Double sided
	Node* head;
	Node* tail;

	// Running size counter
	long count;

	// Locks
	pthread_mutex_t countLock;
	pthread_rwlock_t headLock;
	pthread_rwlock_t tailLock;
};

template <class T>
List<T>::List()
{
	count = 0;
	pthread_mutex_init(&countLock, NULL);
	pthread_rwlock_init(&headLock, NULL);

	head = NULL;
	tail = NULL;
}
template <class T>
List<T>::List(const List<T>& list)
{
	pthread_mutex_init(&countLock, NULL);
	pthread_rwlock_init(&headLock, NULL);

	pthread_rwlock_rdlock(&list.headLock);
	Node* current = NULL;
	for(Node* node = list.head; node != NULL; node = node->next)
	{
		pthread_rwlock_rdlock(&node->lock);
		if(node->prev != NULL)
			pthread_rwlock_unlock(&node->lock);

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

		// If this is the last run
		if(node->next == NULL)
		{
			pthread_rwlock_unlock(node->lock);
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
List<T>::~List()
{
	pthread_mutex_lock(&countLock);
	pthread_rwlock_wrlock(&headLock);
	while(this->head != NULL)
	{
		pthread_rwlock_wrlock(&this->head->lock);
		Node* toDelete = this->head;
		this->head = toDelete->next;
		delete toDelete;
	}

	pthread_mutex_destroy(&countLock);
	pthread_rwlock_destroy(&headLock);
}

template <class T>
T List<T>::front()
{
	pthread_rwlock_rdlock(&this->headLock);
	if(this->head == NULL)
	{
		pthread_rwlock_unlock(&this->headLock);
		return NULL;
	}
	else
	{
		T value = this->head->value;
		pthread_rwlock_unlock(&this->headLock);
		return value;
	}
}

template <class T>
T List<T>::back()
{
	pthread_rwlock_rdlock(&this->headLock);
	if(this->tail == NULL)
	{
		pthread_rwlock_unlock(&this->headLock);
		return NULL;
	}
	else
	{
		T value = this->tail->value;
		pthread_rwlock_unlock(&this->headLock);
		return value;
	}
}

template <class T>
bool List<T>::empty()
{
	pthread_rwlock_rdlock(&this->headLock);
	if(this->head == NULL)
	{
		pthread_rwlock_unlock(&this->headLock);
		return true;
	}
	else
	{
		pthread_rwlock_unlock(&this->headLock);
		return false;
	}
}

template <class T>
long List<T>::size()
{
	// Single operation, shouldn't need a lock
	pthread_mutex_lock(&countLock);
	long value = this->count;
	pthread_mutex_unlock(&countLock);
	return value;
}

template <class T>
void List<T>::pushFront(const T& value)
{
	pthread_rwlock_wrlock(&this->headLock);
	if(this->head == NULL)
	{
		// Create new node and make it head and tail
		this->head = new Node(value);
		this->tail = head;
	}
	else
	{
		// Make new node, set it as new head
		pthread_rwlock_wrlock(&this->head->lock);
		Node* newNode = new Node(value);
		newNode->next = this->head;
		this->head->prev = newNode;
		this->head = newNode;
		pthread_rwlock_unlock(&this->head->next->lock);
	}
	pthread_rwlock_unlock(&this->headLock);

	// Increment counter
	pthread_mutex_lock(&countLock);
	count++;
	pthread_mutex_unlock(&countLock);
}

template <class T>
void List<T>::pushBack(const T& value)
{
	pthread_rwlock_wrlock(&this->headLock);
	if(head == NULL)
	{
		this->head = new Node(value);
		this->tail = head;
	}
	else
	{
		pthread_rwlock_wrlock(&this->tail->lock);
		Node* newNode = new Node(value);
		this->tail->next = newNode;
		newNode->prev = this->tail;
		this->tail = newNode;
		pthread_rwlock_unlock(&this->tail->prev->lock);
	}
	pthread_rwlock_unlock(&this->headLock);

	pthread_mutex_lock(&countLock);
	count++;
	pthread_mutex_unlock(&countLock);
}

template <class T>
T List<T>::popFront()
{
	pthread_rwlock_wrlock(&this->headLock);
	if(this->head == NULL)
	{
		pthread_rwlock_unlock(&this->headLock);
		return NULL;
	}
	else if(head == tail)
	{
		// lock node in case a iterator is currently on it
		pthread_rwlock_wrlock(&this->head->lock);
		// set head and tail to null then unlock
		Node* toDelete = this->head;
		this->head = NULL;
		this->tail = NULL;
		pthread_rwlock_unlock(&this->headLock);

		// increment counter
		pthread_mutex_lock(&countLock);
		count--;
		pthread_mutex_unlock(&countLock);

		// delete old head node and return its value
		T value = toDelete->value;
		delete toDelete;
		return value;
	}
	else
	{
		// Lock head and next node, going to be changed
		pthread_rwlock_wrlock(&this->head->lock);
		pthread_rwlock_wrlock(&this->head->next->lock);

		// Set next head and release headlock
		Node* toDelete = this->head;
		this->head = toDelete->next;
		this->head->prev = NULL;
		pthread_rwlock_unlock(&this->head->lock);
		pthread_rwlock_unlock(&this->headLock);

		// decrement counter
		pthread_mutex_lock(&countLock);
		count--;
		pthread_mutex_unlock(&countLock);

		// delete old head node and return its value
		T value = toDelete->value;
		delete toDelete;
		return value;
	}
}

template <class T>
T List<T>::popBack()
{
	pthread_rwlock_wrlock(&this->headLock);
	if(tail == NULL)
	{
		pthread_rwlock_unlock(&this->headLock);
		return NULL;
	}
	else if(head == tail)
	{
		// lock node, fix pointers, unlock
		pthread_rwlock_wrlock(&this->tail->lock);
		Node* toDelete = this->tail;
		this->head = NULL;
		this->tail = NULL;
		pthread_rwlock_unlock(&this->headLock);

		// decrement counter
		pthread_mutex_lock(&countLock);
		count--;
		pthread_mutex_unlock(&countLock);

		// delete node and return value
		T value = toDelete->value;
		delete toDelete;
		return value;

	}
	else
	{
		// Lock tail nodes
		pthread_rwlock_wrlock(&this->tail->prev->lock);
		pthread_rwlock_wrlock(&this->tail->lock);

		// set next tail and release headlock
		Node* toDelete = this->tail;
		this->tail = toDelete->prev;
		this->tail->next = NULL;
		pthread_rwlock_unlock(&this->tail->lock);
		pthread_rwlock_unlock(&this->headLock);

		// decrement counter
		pthread_mutex_lock(&countLock);
		count--;
		pthread_mutex_unlock(&countLock);

		// delete node and return value
		T value = toDelete->value;
		delete toDelete;
		return value;
	}
}

template <class T>
void List<T>::remove(T value)
{
	// Lock head since starting there
	pthread_rwlock_wrlock(&this->headLock);
	Node* toDelete = NULL;
	Node* current = this->head;
	// Make sure not empty
	if(current == NULL)
	{
		pthread_rwlock_unlock(&this->headLock);
		return;
	}

	// Check head, delete if it is head
	pthread_rwlock_wrlock(&current->lock);
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

		pthread_rwlock_unlock(&this->headLock);
	}
	// If only head then doesnt exist
	else if(current->next == NULL)
	{
		pthread_rwlock_unlock(&current->lock);
		pthread_rwlock_unlock(&this->headLock);
		return;
	}
	// Check next as well to maintain 2 prev locks at all times
	else if(current->next->value == value)
	{
		pthread_rwlock_wrlock(&current->next->lock);
		toDelete = current->next;

		// If deleting tail
		if(toDelete->next == NULL)
		{
			toDelete->prev->next = NULL;
			this->tail = toDelete->prev;
			pthread_rwlock_unlock(&toDelete->prev->lock);
			delete toDelete;
		}
		else
		{
			pthread_rwlock_wrlock(&toDelete->next->lock);
			toDelete->prev->next = toDelete->next;
			toDelete->next->prev = toDelete->prev;
			pthread_rwlock_unlock(&toDelete->prev->lock);
			pthread_rwlock_unlock(&toDelete->next->lock);
			delete toDelete;
		}

		pthread_rwlock_unlock(&this->headLock);
	}
	// Otherwise search for and destroy the node
	else
	{
		pthread_rwlock_unlock(&this->headLock);

		// Get the node that is to be deleted
		while(current->next != NULL)
		{
			pthread_rwlock_wrlock(&current->next->lock);
			pthread_rwlock_unlock(&current->prev->prev->lock);
			current = current->next;
			if(current->value == value)
			{
				toDelete = current;
				break;
			}
		}

		if(toDelete == NULL)
		{
			pthread_rwlock_unlock(&current->prev->lock);
			pthread_rwlock_unlock(&current->lock);
			return;
		}
		else
		{
			// If tail then must make sure pushBack or popBack not running
			if(toDelete->next == NULL)
			{
				// TODO: special case when deleting tail
			}
			else
			{
				pthread_rwlock_wrlock(&toDelete->next->lock);
				toDelete->prev->next = toDelete->next;
				toDelete->next->prev = toDelete->prev;
				pthread_rwlock_unlock(&toDelete->prev->lock);
				pthread_rwlock_unlock(&toDelete->next->lock);
				delete toDelete;
			}
		}
	}

	pthread_mutex_lock(&countLock);
	count--;
	pthread_mutex_unlock(&countLock);
}

template <class T>
class List<T>::Iterator
{
private:
	typename List<T>::Node* current;
public:
	Iterator(List<T>* list)
	{
		pthread_rwlock_rdlock(&list->headLock);
		this->current = list->head;
		if(this->current != NULL)
		{
			pthread_rwlock_rdlock(&current->lock);
		}
		pthread_rwlock_unlock(&list->headLock);
	}

	T value()
	{
		if(current == NULL)
			return NULL;
		else
			return this->current->value;
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
		if(current->next != NULL)
		{
			pthread_rwlock_rdlock(&current->next->lock);
			this->current = this->current->next;
			pthread_rwlock_unlock(&current->prev->lock);
		}
		else
		{
			pthread_rwlock_unlock(&current->lock);
			this->current = this->current->next;
		}
	}
};

template <class T>
class List<T>::WriteIterator
{
private:
	typename List<T>::Node* current;
public:
	WriteIterator(List<T>* list)
	{
		pthread_rwlock_wrlock(&list->headLock);
		this->current = list->head;
		if(this->current != NULL)
		{
			pthread_rwlock_wrlock(&current->lock);
		}
		pthread_rwlock_unlock(&list->headLock);
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
		// If trying to remove head
		// popFront would wait forever for this node to be unlocked
		if(current->prev == NULL)
		{
			// TODO: special case of head remove

		}
		// popBack would wait forever for this node to be unlocked
		else if(current->next == NULL)
		{
			// TODO: special case of tail removal
		}
		else
		{
			pthread_rwlock_wrlock(&current->next->lock);
			typename List<T>::Node* toDelete = current;
			current->prev->next = current->next;
			current->next->prev = current->prev;
			current = current->next;

			delete toDelete;
		}
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
		if(current->next != NULL)
		{
			pthread_rwlock_wrlock(&current->next->lock);
			this->current = this->current->next;
			pthread_rwlock_unlock(&current->prev->lock);
		}
		else
		{
			pthread_rwlock_unlock(&current->lock);
			this->current = this->current->next;
		}
	}
};

template <class T>
typename List<T>::Iterator List<T>::begin()
{
	return Iterator(this);
}
template <class T>
typename List<T>::WriteIterator List<T>::beginWrite()
{
	return Iterator(this);
}

#endif	/* _LIST_H */
