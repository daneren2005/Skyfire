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

#ifndef _PRIORITY_QUEUE_H
#define	_PRIORITY_QUEUE_H

#include "Exceptions.h"
#include "Comparison.h"
#include "Types.h"
#include <cmath>

// Default to min PriorityQueue
template <class T, class Compare = LessThan<T> >
class PriorityQueue
{
public:
	PriorityQueue();
	PriorityQueue(const PriorityQueue<T, Compare>& orig);
	~PriorityQueue();

	void insert(const T& value);
	T remove();
	T peek();
	bool exists(const T& value);
	
	ulong size();
	bool empty();

	PriorityQueue& operator=(const PriorityQueue& orig);

	class Iterator;
	Iterator begin();
private:
	class Node
	{
	public:
		Node(ulong size)
		{
			value = new T[size];
			max = 0;
			total = size;
			next = 0x0;
			prev = 0x0;
		}
		~Node()
		{
			if(next != 0x0)
				delete next;
			delete[] value;
		}

		T* value;
		ulong max;
		ulong total;
		Node* next;
		Node* prev;
	};

	Node* root;
	Node* bot;
	ulong count;
	Compare c;
};

template <class T, class Compare>
PriorityQueue<T, Compare>::PriorityQueue()
{
	this->root = 0x0;
	this->bot = 0x0;
	count = 0;
}
template <class T, class Compare>
PriorityQueue<T, Compare>::PriorityQueue(const PriorityQueue& orig)
{
	if(orig.root == 0x0)
	{
		this->root = 0x0;
		this->bot = 0x0;
		this->count = 0;
		return;
	}

	Node* currThis = new Node(1);
	currThis->value[0] = orig.root->value[0];
	this->root = currThis;

	Node* currOrig = orig.root;
	while(currOrig->next != 0x0)
	{
		currOrig = currOrig->next;
		currThis->next = new Node(currOrig->total);
		currThis->next->prev = currThis;
		currThis = currThis->next;

		// Copy contents over
		currThis->max = currOrig->max;
		for(ulong i = 0; i < currThis->max; i++)
		{
			currThis->value[i] = currOrig->value[i];
		}
	}

	this->bot = currThis;
}
template <class T, class Compare>
PriorityQueue<T, Compare>::~PriorityQueue()
{
	if(root != 0x0)
		delete root;
}

template <class T, class Compare>
void PriorityQueue<T, Compare>::insert(const T& value)
{
	// Starting out
	if(root == 0x0)
	{
		root = new Node(1);
		root->value[0] = value;
		root->max++;
		bot = root;
	}
	else
	{
		// bot level is maxed out already
		if(bot->total == bot->max)
		{
			Node* newNode = new Node(bot->max * 2);
			bot->next = newNode;
			newNode->prev = bot;
			bot = newNode;
		}

		bot->value[bot->max] = value;
		bot->max++;

		// Bubble up
		Node* curr = bot;
		ulong i = bot->max - 1;
		ulong j = i / 2;

		while(curr->prev != 0x0 && c(curr->value[i], curr->prev->value[j]))
		{
			// Swap
			T temp = curr->value[i];
			curr->value[i] = curr->prev->value[j];
			curr->prev->value[j] = temp;

			curr = curr->prev;
			i = j;
			j = i / 2;
		}
	}

	this->count++;
}
template <class T, class Compare>
T PriorityQueue<T, Compare>::remove()
{
	// Make sure not empty
	if(root == 0x0)
	{
		throw InvalidOperation();
	}

	T temp = root->value[0];

	// If returning root value
	if(root == bot)
	{
		delete root;
		root = 0x0;
		bot = 0x0;
		count--;
		return temp;
	}

	bot->max--;
	root->value[0] = bot->value[bot->max];

	// Remove empty node
	if(bot->max == 0)
	{
		bot = bot->prev;
		delete bot->next;
		bot->next = 0x0;
	}

	// Bubble down
	Node* curr = root;
	ulong i = 0;
	ulong j = 0;
	while(curr->next != 0x0)
	{
		// Switch with min child
		T val = curr->value[i];
		bool done = true;
		if(j < curr->next->max && c(curr->next->value[j], val))
		{
			val = curr->next->value[j];
			done = false;
		}
		if(j + 1 < curr->next->max && c(curr->next->value[j + 1], val))
		{
			j++;
			val = curr->next->value[j];
			done = false;
		}

		if(done)
			break;

		curr->next->value[j] = curr->value[i];
		curr->value[i] = val;

		i = j;
		j = j * 2;
		curr = curr->next;
	}

	this->count--;
	return temp;
}
template <class T, class Compare>
T PriorityQueue<T, Compare>::peek()
{
	return root->value[0];
}
template <class T, class Compare>
bool PriorityQueue<T, Compare>::exists(const T& value)
{
	for(PriorityQueue<T, Compare>::Iterator it = this->begin(); !it; it++)
	{
		if(it.value() == value)
			return true;
	}
	
	return false;
}

template <class T, class Compare>
ulong PriorityQueue<T, Compare>::size()
{
	return count;
}
template <class T, class Compare>
bool PriorityQueue<T, Compare>::empty()
{
	return count == 0;
}

template <class T, class Compare>
PriorityQueue<T, Compare>& PriorityQueue<T, Compare>::operator=(const PriorityQueue& orig)
{
	if(this->root != 0x0)
		delete this->root;

	if(orig.root == 0x0)
	{
		this->root = 0x0;
		this->bot = 0x0;
		this->count = 0;
		return;
	}

	Node* currThis = new Node(1);
	currThis->value[0] = orig.root->value[0];
	this->root = currThis;

	Node* currOrig = orig.root;
	while(currOrig->next != 0x0)
	{
		currOrig = currOrig->next;
		currThis->next = new Node(currOrig->total);
		currThis->next->prev = currThis;
		currThis = currThis->next;

		// Copy contents over
		currThis->max = currOrig->max;
		for(ulong i = 0; i < currThis->max; i++)
		{
			currThis->value[i] = currOrig->value[i];
		}
	}

	this->bot = currThis;
}

template <class T, class Compare>
class PriorityQueue<T, Compare>::Iterator
{
public:
	Iterator(PriorityQueue<T, Compare>* PriorityQueue)
	{
		curr = PriorityQueue->root;
		i = 0;
	}

	T value()
	{
		return curr->value[i];
	}

	bool operator!()
	{
		if(curr == 0x0)
			return false;
		if(curr->next != 0x0)
			return true;
		else
			return i < curr->max;
	}

	void operator++(int)
	{
		i++;
		if(i >= curr->max && curr->next != 0x0)
		{
			i = 0;
			curr = curr->next;
		}
	}
private:
	Node* curr;
	ulong i;
};

template <class T, class Compare>
typename PriorityQueue<T, Compare>::Iterator PriorityQueue<T, Compare>::begin()
{
	return Iterator(this);
}

#endif
