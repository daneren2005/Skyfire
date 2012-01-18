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

#ifndef _LIST_H_
#define	_LIST_H_

#include "SharedLock.h"
#include "Console.h"

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
	List(List<T>& list);
	~List();

	T front();
	T back();
	bool empty();
	long size();

	void pushFront(const T& value);
	void pushBack(const T& value);
	T popFront();
	T popBack();
	void insert(const T& value);
	void remove(const T& value);
	bool exists(const T& value);
	void sort();
	template <class Compare>
	void sort(Compare c);
	
	List& operator=(List& orig);
	
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
			this->next = 0x0;
			this->prev = 0x0;
		}

		T value;
		Node* next;
		Node* prev;

		SharedLock lock;
	};

	// Double sided
	Node* head;
	Node* tail;

	// Running size counter
	long count;

	// Locks
	Lock countLock;
	Lock headLock;
	
	template <class Compare>
	Node* mergeSort(List<T>::Node* start, ulong size, Compare& c);
};

template <class T>
List<T>::List()
{
	count = 0;

	head = 0x0;
	tail = 0x0;
}
template <class T>
List<T>::List(List<T>& list)
{
	list.headLock.lock();
	Node* current = 0x0;
	for(Node* node = list.head; node != 0x0; node = node->next)
	{
		node->lock.readLock();
		if(node->prev != 0x0)
			node->lock.readLock();

		// If its the first run
		if(this->head == 0x0)
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
		if(node->next == 0x0)
		{
			node->lock.unlock();
		}
	}

	if(current == 0x0)
	{
		this->head = 0x0;
		this->tail = 0x0;
	}
	else
	{
		this->tail = current;
	}
}

template <class T>
List<T>::~List()
{
	countLock.lock();
	headLock.lock();
	while(this->head != 0x0)
	{
		this->head->lock.writeLock();
		Node* toDelete = this->head;
		this->head = toDelete->next;
		delete toDelete;
	}
}

template <class T>
T List<T>::front()
{
	headLock.lock();
	if(this->head == 0x0)
	{
		headLock.unlock();
		return 0x0;
	}
	else
	{
		head->lock.readLock();
		T value = this->head->value;
		head->lock.unlock();
		headLock.unlock();
		return value;
	}
}

template <class T>
T List<T>::back()
{
	headLock.lock();
	if(this->tail == 0x0)
	{
		headLock.unlock();
		return 0x0;
	}
	else
	{
		tail->lock.readLock();
		T value = this->tail->value;
		tail->lock.unlock();
		headLock.unlock();
		return value;
	}
}

template <class T>
bool List<T>::empty()
{
	headLock.lock();
	if(this->head == 0x0)
	{
		headLock.unlock();
		return true;
	}
	else
	{
		headLock.unlock();
		return false;
	}
}

template <class T>
long List<T>::size()
{
	// Single operation, shouldn't need a lock
	countLock.lock();
	long value = this->count;
	countLock.unlock();
	return value;
}

template <class T>
void List<T>::pushFront(const T& value)
{
	headLock.lock();
	if(this->head == 0x0)
	{
		// Create new node and make it head and tail
		this->head = new Node(value);
		this->tail = head;
	}
	else
	{
		// Make new node, set it as new head
		this->head->lock.writeLock();
		Node* newNode = new Node(value);
		newNode->next = this->head;
		this->head->prev = newNode;
		this->head = newNode;
		this->head->next->lock.unlock();
	}
	headLock.unlock();

	// Increment counter
	countLock.lock();
	count++;
	countLock.unlock();
}

template <class T>
void List<T>::pushBack(const T& value)
{
	headLock.lock();
	if(head == 0x0)
	{
		this->head = new Node(value);
		this->tail = head;
	}
	else
	{
		this->tail->lock.writeLock();
		Node* newNode = new Node(value);
		this->tail->next = newNode;
		newNode->prev = this->tail;
		this->tail = newNode;
		this->tail->prev->lock.unlock();
	}
	headLock.unlock();

	countLock.lock();
	count++;
	countLock.unlock();
}

template <class T>
T List<T>::popFront()
{
	headLock.lock();
	if(this->head == 0x0)
	{
		headLock.unlock();
		return 0x0;
	}
	else if(head == tail)
	{
		// lock node in case a iterator is currently on it
		this->head->lock.writeLock();
		// set head and tail to null then unlock
		Node* toDelete = this->head;
		this->head = 0x0;
		this->tail = 0x0;
		headLock.unlock();

		// increment counter
		countLock.lock();
		count--;
		countLock.unlock();

		// delete old head node and return its value
		T value = toDelete->value;
		delete toDelete;
		return value;
	}
	else
	{
		// Lock head and next node, going to be changed
		this->head->lock.writeLock();
		this->head->next->lock.writeLock();

		// Set next head and release headlock
		Node* toDelete = this->head;
		this->head = toDelete->next;
		this->head->prev = 0x0;
		this->head->lock.unlock();
		headLock.unlock();

		// decrement counter
		countLock.lock();
		count--;
		countLock.unlock();

		// delete old head node and return its value
		T value = toDelete->value;
		delete toDelete;
		return value;
	}
}

template <class T>
T List<T>::popBack()
{
	headLock.lock();
	if(tail == 0x0)
	{
		headLock.unlock();
		return 0x0;
	}
	else if(head == tail)
	{
		// lock node, fix pointers, unlock
		this->tail->lock.writeLock();
		Node* toDelete = this->tail;
		this->head = 0x0;
		this->tail = 0x0;
		headLock.unlock();

		// decrement counter
		countLock.lock();
		count--;
		countLock.unlock();

		// delete node and return value
		T value = toDelete->value;
		delete toDelete;
		return value;

	}
	else
	{
		// Lock tail nodes
		this->tail->prev->lock.writeLock();
		this->tail->lock.writeLock();

		// set next tail and release headlock
		Node* toDelete = this->tail;
		this->tail = toDelete->prev;
		this->tail->next = 0x0;
		this->tail->lock.unlock();
		headLock.unlock();

		// decrement counter
		countLock.lock();
		count--;
		countLock.unlock();

		// delete node and return value
		T value = toDelete->value;
		delete toDelete;
		return value;
	}
}

template <class T>
inline void List<T>::insert(const T& value)
{
	this->pushBack(value);
}
template <class T>
void List<T>::remove(const T& value)
{
	// Lock head since starting there
	headLock.lock();
	Node* toDelete = 0x0;
	Node* current = this->head;
	// Make sure not empty
	if(current == 0x0)
	{
		headLock.unlock();
		return;
	}

	// Check head, delete if it is head
	current->lock.writeLock();
	if(current->value == value)
	{
		// Delete head then and exit
		toDelete = current;
		if(head->next == 0x0)
		{
			delete this->head;
			this->head = 0x0;
			this->tail = 0x0;
		}
		else
		{
			this->head = toDelete->next;
			delete toDelete;
			this->head->prev = 0x0;
		}

		headLock.unlock();
	}
	// If only head then doesnt exist
	else if(current->next == 0x0)
	{
		current->lock.unlock();
		headLock.unlock();
		return;
	}
	// Otherwise search for and destroy the node
	else
	{
		headLock.unlock();

		// Get the node that is to be deleted
		current = current->next;
		current->lock.writeLock();
		while(current->next != 0x0)
		{
			current->next->lock.writeLock();
				current->prev->lock.unlock();
			current = current->next;
			if(current->value == value)
			{
				toDelete = current;
				break;
			}
		}

		if(toDelete == 0x0)
		{
			current->prev->lock.unlock();
			current->lock.unlock();
			return;
		}
		else
		{
			// If tail then must make sure pushBack or popBack not running
			if(toDelete->next == 0x0)
			{
				// TODO: special case when deleting tail
				// toDelete->prev->next = 0x0;
				current->prev->lock.unlock();
				current->lock.unlock();
				// delete toDelete;
				return;
			}
			else
			{
				toDelete->next->lock.writeLock();
				toDelete->prev->next = toDelete->next;
				toDelete->next->prev = toDelete->prev;
				toDelete->prev->lock.unlock();
				toDelete->next->lock.unlock();
				delete toDelete;
			}
		}
	}

	countLock.lock();
	count--;
	countLock.unlock();
}
template <class T>
bool List<T>::exists(const T& value)
{
	// Lock head since starting there
	headLock.lock();
	if(head == 0x0)
	{
		headLock.unlock();
		return false;
	}
	
	Node* current = head;
	current->lock.readLock();
	headLock.unlock();
	
	while(current->next != 0x0)
	{
		if(current->value == value)
		{
			current->lock.unlock();
			return true;
		}
		
		current->next->lock.lock();
		current = current->next;
		current->prev->lock.unlock();
	}
	
	if(current->value == value)
	{
		current->lock.unlock();
		return true;
	}

	current->lock.unlock();
	return false;
}

template <class T>
void List<T>::sort()
{	
	LessThan<T> c;
	sort(c);
}

template <class T>
template <class Compare>
void List<T>::sort(Compare c)
{
	// Lock whole list
	headLock.lock();
	for(Node* node = this->head; node != 0x0; node = node->next)
	{
		node->lock.writeLock();
	}

	mergeSort(head, count, c);

	// Unlock whole list
	for(Node* node = this->head; node != 0x0; node = node->next)
	{
		node->lock.unlock();
	}
	headLock.unlock();
}

template <class T>
template <class Compare>
typename List<T>::Node* List<T>::mergeSort(List<T>::Node* start, ulong size, Compare& c)
{
	if(size <= 1)
		return start;
	
	ulong sizeLeft = size / 2;
	ulong sizeRight = sizeLeft + size % 2;
	Node* left = start;
	Node* right = start;
	for(ulong i = 0; i < sizeLeft; i++)
	{
		right = right->next;
	}
	
	left = mergeSort(left, sizeLeft, c);
	right = mergeSort(right, sizeRight, c);
	start = left;
	
	// Sort
	ulong i = 0;
	ulong j = 0;
	while(i < sizeLeft && j < sizeRight)
	{
		if(c(left->value, right->value))
		{
			left = left->next;
			i++;
		}
		else
		{
			if(start == left)
				start = right;
			
			// Remove right from Right list
			Node* temp = right->next;
			right->prev->next = right->next;
			
			if(right->next == 0x0)
				tail = right->prev;
			else
				right->next->prev = right->prev;
			
			// Move Right to left of Left
			right->prev = left->prev;
			right->next = left;
			
			if(left->prev == 0x0)
				head = right;
			else
				left->prev->next = right;
			left->prev = right;
			
			// Advance left past moved node
			right = temp;
			
			j++;
		}
	}
	
	return start;
}

template <class T>
List<T>& List<T>::operator=(List& orig)
{
	countLock.lock();
	headLock.lock();
	
	// Delete old stuff
	while(this->head != 0x0)
	{
		this->head->lock.writeLock();
		Node* toDelete = this->head;
		this->head = toDelete->next;
		delete toDelete;
	}
	
	// Copy new stuff
	orig.headLock.lock();
	Node* current = 0x0;
	for(Node* node = orig.head; node != 0x0; node = node->next)
	{
		node->lock.readLock();
		if(node->prev != 0x0)
			node->prev->lock.unlock();

		// If its the first run
		if(this->head == 0x0)
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
		if(node->next == 0x0)
		{
			node->lock.unlock();
		}
	}

	if(current == 0x0)
	{
		this->head = 0x0;
		this->tail = 0x0;
	}
	else
	{
		this->tail->node = current;
	}

	orig.countLock.lock();
	this->count = orig.count;
	orig.countLock.unlock();
	countLock.unlock();

	headLock.unlock();
	
	return *this;
}

template <class T>
class List<T>::Iterator
{
private:
	typename List<T>::Node* current;
public:
	Iterator(List<T>* list)
	{
		list->headLock.lock();
		this->current = list->head;
		if(this->current != 0x0)
		{
			current->lock.readLock();
		}
		list->headLock.unlock();
	}

	T value()
	{
		if(current == 0x0)
			return 0x0;
		else
			return this->current->value;
	}

	// Operator Overloading
	bool operator !()
	{
		if(this->current == 0x0)
			return false;
		else
			return true;
	}
	void operator ++(int)
	{
		if(current->next != 0x0)
		{
			current->next->lock.readLock();
			this->current = this->current->next;
			current->prev->lock.unlock();
		}
		else
		{
			current->lock.unlock();
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
		headLock.lock();
		this->current = list->head;
		if(this->current != 0x0)
		{
			current->lock.writeLock();
		}
		headLock.unlock();
	}

	T value()
	{
		if(current == 0x0)
			return 0x0;
		else
			return this->current->value;
	}

	T remove()
	{
		// If trying to remove head
		// popFront would wait forever for this node to be unlocked
		if(current->prev == 0x0)
		{
			// TODO: special case of head remove

		}
		// popBack would wait forever for this node to be unlocked
		else if(current->next == 0x0)
		{
			// TODO: special case of tail removal
		}
		else
		{
			current->next->lock.writeLock();
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
		if(this->current == 0x0)
			return false;
		else
			return true;
	}
	void operator ++(int)
	{
		if(current->next != 0x0)
		{
			current->next->lock.writeLock();
			this->current = this->current->next;
			current->prev->lock.unlock();
		}
		else
		{
			current->lock.unlock();
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
