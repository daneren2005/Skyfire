/* 
 * File:   List.h
 * Author: scott
 *
 * Created on July 7, 2010, 7:17 PM
 */

#ifndef _LIST_H
#define	_LIST_H

// For use of NULL
// #include <iostream>
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
private:
	class Node
	{
	public:
		Node(T value)
		{
			this->value = value;
			this->next = NULL;
			this->prev = NULL;
			pthread_rwlock_init(&lock, NULL);
		}
		~Node()
		{
			pthread_rwlock_destroy(&lock);
		}

		void readLock()
		{
			pthread_rwlock_rdlock(&lock);
		}
		void readUnlock()
		{
			pthread_rwlock_unlock(&lock);
		}
		void writeLock()
		{
			pthread_rwlock_wrlock(&lock);
		}
		void writeUnlock()
		{
			pthread_rwlock_unlock(&lock);
		}

		T value;
		Node* next;
		Node* prev;
		
		// Locks
		pthread_rwlock_t lock;
	};

	// Double sided
	Node* head;
	Node* tail;

	// Running size counter
	long count;

	friend class Iterator<T>;

	// Locks
	// Head lock to avoid deleting head and being sent into infinite wait
	pthread_mutex_t headLock;
	pthread_mutex_t tailLock;
	pthread_mutex_t countLock;
public:
	// Constructor/Destructor
	List();
	List(const List<T>& list);
	~List();

	// General Access
	T front();
	T back();
	bool empty();
	int size();
	Iterator<T> begin(bool write = true);

	// Insert
	void push_front(T value);
	void push_back(T value);

	// Delete
	T pop_front();
	T pop_back();
	void remove(T value);
};

template <class T>
List<T>::List()
{
	head = NULL;
	tail = NULL;
	count = 0;
	pthread_mutex_init(&headLock, NULL);
	pthread_mutex_init(&tailLock, NULL);
	pthread_mutex_init(&countLock, NULL);
}
template <class T>
List<T>::List(const List<T>& list)
{
	this->head = NULL;
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
			current = current->next;
		}
	}
}

template <class T>
List<T>::~List()
{
	while(this->head != NULL)
	{
		Node* toDelete = this->head;
		this->head = toDelete->next;
		delete toDelete;
	}
}

template <class T>
T List<T>::front()
{
	if(this->head == NULL)
	{
		return NULL;
	}
	else
	{
		pthread_mutex_lock(&headLock);
		this->head->readLock();
		pthread_mutex_unlock(&headLock);
		T value = this->head->value;
		this->head->readUnlock();
		return value;
	}
}

template <class T>
T List<T>::back()
{
	// Cant really lock, just 1 operation...
	pthread_mutex_lock(&headLock);
	if(this->tail == NULL)
	{
		pthread_mutex_unlock(&headLock);
		return NULL;
	}
	else
	{
		T value = this->tail->value;
		return value;
	}
}

template <class T>
bool List<T>::empty()
{
	// Cant really lock, just 1 operation...
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
int List<T>::size()
{
	// Single operation, shouldn't need a lock
	pthread_mutex_lock(&countLock);
	long value = this->count;
	pthread_mutex_unlock(&countLock);
	return value;
}

template <class T>
Iterator<T> List<T>::begin(bool write)
{
	return Iterator<T>(this);
}

template <class T>
void List<T>::push_front(T value)
{
	pthread_mutex_lock(&headLock);
	if(head == NULL)
	{
		// Create new node and make it head and tail
		this->head = new Node(value);
		this->tail = head;
	}
	else
	{
		// Lock head node, alter it, then unlock
		this->head->writeLock();
		Node* newNode = new Node(value);
		newNode->next = this->head;
		this->head->prev = newNode;
		this->head = newNode;
		this->head->next->writeUnlock();
	}
	pthread_mutex_unlock(&headLock);

	// Increment counter
	pthread_mutex_lock(&countLock);
	count++;
	pthread_mutex_unlock(&countLock);
}

template <class T>
void List<T>::push_back(T value)
{
	pthread_mutex_lock(&headLock);
	
	if(head == NULL)
	{
		this->head = new Node(value);
		this->tail = head;
		pthread_mutex_unlock(&headLock);
	}
	else if(head == tail)
	{
		this->tail->writeLock();
		Node* newNode = new Node(value);
		this->tail->next = newNode;
		newNode->prev = this->tail;
		this->tail = newNode;
		this->tail->prev->writeUnlock();
		pthread_mutex_unlock(&headLock);
	}
	else
	{
		this->tail->writeLock();
		Node* newNode = new Node(value);
		this->tail->next = newNode;
		newNode->prev = this->tail;
		this->tail = newNode;
		this->tail->prev->writeUnlock();
		pthread_mutex_unlock(&headLock);
	}

	pthread_mutex_lock(&countLock);
	count++;
	pthread_mutex_unlock(&countLock);
}

template <class T>
T List<T>::pop_front()
{
	pthread_mutex_lock(&headLock);
	if(this->head == NULL)
	{
		pthread_mutex_unlock(&headLock);
		return NULL;
	}
	else if(head->next == NULL)
	{
		// lock node, fix pointers, unlock
		this->head->writeLock();
		Node* head = this->head;
		this->head = NULL;
		this->tail = NULL;
		pthread_mutex_unlock(&headLock);

		// increment counter
		pthread_mutex_lock(&countLock);
		count--;
		pthread_mutex_unlock(&countLock);

		// delete old head node and return its value
		T value = head->value;
		delete head;
		return value;
	}
	else
	{
		// Lock nodes
		this->head->writeLock();
		this->head->next->writeLock();

		// Set next head and release headlock
		Node* toDelete = head;
		this->head = toDelete->next;
		pthread_mutex_unlock(&headLock);

		// fix head node, release head node
		toDelete->next->prev = NULL;
		this->head->writeUnlock();

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
T List<T>::pop_back()
{
	pthread_mutex_lock(&headLock);
	if(head == NULL)
	{
		pthread_mutex_unlock(&headLock);
		return NULL;
	}
	else if(head == tail)
	{
		// lock node, fix pointers, unlock
		this->tail->writeLock();
		Node* toDelete = this->tail;
		this->head = NULL;
		this->tail = NULL;
		pthread_mutex_unlock(&headLock);

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
		this->tail->prev->writeLock();
		this->tail->writeLock();

		// set next tail and release headlock
		Node* toDelete = this->tail;
		this->tail = toDelete->prev;
		this->tail->next = NULL;
		this->tail->writeUnlock();
		pthread_mutex_unlock(&headLock);

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
	// Get the node that is to be deleted
	Node* toDelete = NULL;
	for(Node* current = this->head; current != NULL; current = current->next)
	{
		if(current->value == value)
		{
			toDelete = current;
			break;
		}
	}

	if(toDelete == NULL)
		return;

	// Cant call already defined function cause mutex blocked and will wait
	if(toDelete == this->head)
	{
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
	else if(toDelete == this->tail)
	{
		if(head->next == NULL)
		{
			delete this->head;
			this->head = NULL;
			this->tail = NULL;
		}
		else
		{
			this->tail = toDelete->prev;
			delete toDelete;
			this->tail->next = NULL;
		}
	}
	else
	{
		(toDelete->prev)->next = (toDelete->next);
		(toDelete->next)->prev = (toDelete->prev);
		delete toDelete;
	}

	count--;
}

// ----------------------- Iterator Class
template <class T>
class Iterator
{
private:
	typename List<T>::Node* current;
public:
	Iterator(List<T>* list);

	T value();

	// Operator Overloading
	bool operator !();
	void operator ++();
	void operator ++(int);
};

template <class T>
Iterator<T>::Iterator(List<T>* list)
{
	this->current = list->head;
}

template <class T>
T Iterator<T>::value()
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

template <class T>
bool Iterator<T>::operator !()
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

template <class T>
void Iterator<T>::operator ++()
{
	if(current != NULL)
	{
		this->current = this->current->next;
	}
}
template <class T>
void Iterator<T>::operator ++(int i)
{
	if(current != NULL)
	{
		this->current = this->current->next;
	}
}

#endif	/* _LIST_H */

