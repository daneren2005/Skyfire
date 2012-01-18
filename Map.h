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

#ifndef _MAP_H_
#define	_MAP_H_

#include "BasicList.h"
#include "Exceptions.h"

#include "Console.h"

template <class Value, class Key>
class Map
{
public:
	Map();
	Map(const Map& orig);
	~Map();

	bool empty() const;
	long size() const;
	
	void insert(const Value& value, const Key& key);
	Value remove(const Key& key);
	Value search(const Key& key) const;
	bool exists(const Key& key) const;

	Value& operator[](const Key& key);
	const Value& operator[](const Key& key) const;
	Map& operator=(const Map& orig);

	class InOrderIterator;
	class DepthFirstIterator;
	class BreadthFirstIterator;
	typedef InOrderIterator Iterator;

	Iterator begin();
	InOrderIterator beginInOrder();
	DepthFirstIterator beginDepthFirst();
	BreadthFirstIterator beginBreadthFirst();
private:
	class Node
	{
	public:
		Node(const Value& value, const Key& key, bool red = true)
		{
			this->key = key;
			this->value = value;
			this->parent = NULL;
			this->left = NULL;
			this->right = NULL;
			this->red = red;
		}

		Key key;
		Value value;
		Node* parent;
		Node* left;
		Node* right;
		bool red;
	};

	Node* root;
	long count;

	Node* findClosestMatch(const Key& key) const;
	Node* findUncle(Node* node) const;
	Node* findGrandparent(Node* node) const;
	Node* findSibling(Node* node) const;

	void checkInsertion(Node* node);
	void checkDeletion(Node* node);
	void rotateLeft(Node* node);
	void rotateRight(Node* node);
	
	void recursiveCopy(Node* thisNode, Node* origNode);
	void recursiveRemove(Node* current);
};

template <class Value, class Key>
Map<Value, Key>::Map()
{
	this->root = 0x0;
	this->count = 0;
}

template <class Value, class Key>
Map<Value, Key>::Map(const Map& orig)
{
	if(orig.root == 0x0)
	{
		this->root = 0x0;
		this->count = 0;
	}
	else
	{
		this->root = new Node(orig.root->value, orig.root->key, orig.root->red);
		this->count = orig.count;

		recursiveCopy(this->root, orig.root);
	}
}

template <class Value, class Key>
Map<Value, Key>::~Map()
{
	recursiveRemove(root);
}

template <class Value, class Key>
bool Map<Value, Key>::empty() const
{
	return root == 0x0;
}
template <class Value, class Key>
long Map<Value, Key>::size() const
{
	return this->count;
}

template <class Value, class Key>
void Map<Value, Key>::insert(const Value& value, const Key& key)
{
	Node* closest = findClosestMatch(key);
	Node* newNode = new Node(value, key);

	// Empty tree
	if(closest == 0x0)
	{
		root = newNode;
	}
	else if(closest->key == key)
	{
		closest->value = value;
		return;
	}
	else
	{
		// Insert to left
		if(key < closest->key)
		{
			closest->left = newNode;
		}
		// Insert to right
		else
		{
			closest->right = newNode;
		}

		newNode->parent = closest;
	}

	checkInsertion(newNode);
	this->count++;
}

template <class Value, class Key>
Value Map<Value, Key>::remove(const Key& key)
{
	Node* node = findClosestMatch(key);

	if(node == 0x0 || node->key != key)
	{
		throw OutOfRange();
	}
	else if(node->parent == 0x0)
	{
		root = 0x0;
	}

	checkDeletion(node);
	this->count--;
	return node->value;
}

template <class Value, class Key>
Value Map<Value, Key>::search(const Key& key) const
{
	Node* node = findClosestMatch(key);

	if(node == 0x0 || node->key != key)
	{
		throw OutOfRange();
	}

	return node->value;
}

template <class Value, class Key>
bool Map<Value, Key>::exists(const Key& key) const
{
	Node* node = findClosestMatch(key);

	if(node == 0x0 || node->key != key)
	{
		return false;
	}

	return true;
}

template <class Value, class Key>
Value& Map<Value, Key>::operator[](const Key& key)
{
	Node* closest = findClosestMatch(key);
	if(closest->key == key)
	{
		return closest->value;
	}
	else
	{
		// TODO: speed up, waste of resources
		Value value;
		this->insert(value, key);
		closest = findClosestMatch(key);
		return closest->value;
	}
}
template <class Value, class Key>
const Value& Map<Value, Key>::operator[](const Key& key) const
{
	Node* closest = findClosestMatch(key);
	if(closest->key == key)
	{
		return closest->value;
	}
	else
	{
		throw OutOfRange();
	}
}
template <class Value, class Key>
Map<Value, Key>& Map<Value, Key>::operator=(const Map& orig)
{
	if(this == &orig)
		return *this;
	
	recursiveRemove(root);
	
	if(orig.root == 0x0)
	{
		this->root = 0x0;
		this->count = 0;
	}
	else
	{
		this->root = new Node(orig.root->value, orig.root->key, orig.root->red);
		this->count = orig.count;

		recursiveCopy(this->root, orig.root);
	}
	
	return *this;
}

template <class Value, class Key>
typename Map<Value, Key>::Node* Map<Value, Key>::findClosestMatch(const Key& key) const
{
	if(root == 0x0)
	{
		return 0x0;
	}

	Node* current = root;
	while(true)
	{
		// Exact match
		if(key == current->key)
		{
			return current;
		}
		// Go left
		else if(key < current->key)
		{
			// As far left as it will go
			if(current->left == NULL)
			{
				return current;
			}
			// Go further down
			else
			{
				current = current->left;
			}
		}
		// Go right
		else
		{
			// As far right as it will go
			if(current->right == NULL)
			{
				return current;
			}
			// Go further down
			else
			{
				current = current->right;
			}
		}
	}
}

template <class Value, class Key>
typename Map<Value, Key>::Node* Map<Value, Key>::findUncle(Node* node) const
{
	Node* grandparent = findGrandparent(node);
	if(grandparent == 0x0)
	{
		return 0x0;
	}
	else if(node->parent == grandparent->left)
	{
		return grandparent->right;
	}
	else
	{
		return grandparent->left;
	}
}
template <class Value, class Key>
typename Map<Value, Key>::Node* Map<Value, Key>::findGrandparent(Node* node) const
{
	if(node->parent != 0x0)
	{
		return node->parent->parent;
	}
	else
	{
		return 0x0;
	}
}
template <class Value, class Key>
typename Map<Value, Key>::Node* Map<Value, Key>::findSibling(Node* node) const
{
	if(node == node->parent->left)
	{
		return node->parent->right;
	}
	else
	{
		return node->parent->left;
	}
}

template <class Value, class Key>
void Map<Value, Key>::checkInsertion(Node* node)
{
	if(node->parent == 0x0)
	{
		node->red = false;
	}
	else if(node->parent->red == true)
	{
		Node* uncle = findUncle(node);
		Node* grandparent = findGrandparent(node);

		if(uncle != 0x0 && uncle->red == true)
		{
			node->parent->red = false;
			uncle->red = false;
			grandparent->red = true;
			checkInsertion(grandparent);
		}
		else
		{
			if(node == node->parent->right && node->parent == grandparent->left)
			{
				rotateLeft(node->parent);
				node = node->left;
			}
			else if(node == node->parent->left && node->parent == grandparent->right)
			{
				rotateRight(node->parent);
				node = node->right;
			}

			node->parent->red = false;
			grandparent->red = true;
			if(node == node->parent->left && node->parent == grandparent->left)
			{
				rotateRight(grandparent);
			}
			else
			{
				rotateLeft(grandparent);
			}
		}
	}
}
template <class Value, class Key>
void Map<Value, Key>::checkDeletion(Node* node)
{
	if(node->parent != 0x0)
	{
		Node* sibling = findSibling(node);
		
		if(sibling->red == true)
		{
			node->parent->red = true;
			sibling->red = false;
			
			if(node == node->parent->left)
			{
				rotateLeft(node->parent);
			}
			else
			{
				rotateRight(node->parent);
			}

			if(node->parent->red == false && sibling->red == false &&
				sibling->left->red == false && sibling->right->red == false)
			{
				sibling->red = true;
				checkDeletion(node->parent);
			}
			else
			{
				if(node->parent->red == true && sibling->red == false &&
					sibling->left->red == false && sibling->right->red == false)
				{
					sibling->red = true;
					node->parent->red = false;
				}
				else
				{
					if(sibling->red == false)
					{
						if(node == node->parent->left && sibling->right->red == false &&
							sibling->left->red == true)
						{
							sibling->red = true;
							sibling->left->red = false;
							rotateRight(sibling);
						}
						else if(node == node->parent->right && sibling->left->red == false &&
							sibling->right->red == true)
						{
							sibling->red = true;
							sibling->right->red = false;
							rotateLeft(sibling);
						}

						sibling->red = node->parent->red;
						node->parent->red = false;

						if(node == node->parent->left)
						{
							sibling->right->red = false;
							rotateLeft(node->parent);
						}
						else
						{
							sibling->left->red = false;
							rotateRight(node->parent);
						}
					}
				}
			}
		}
	}
}

template <class Value, class Key>
void Map<Value, Key>::rotateLeft(Node* node)
{
	Node* temp = node->right;
	node->right = temp->left;

	if(temp->left != 0x0)
	{
		temp->left->parent = node;
	}

	temp->parent = node->parent;
	if(node->parent == 0x0)
	{
		this->root = temp;
	}
	else if(node == node->parent->left)
	{
		node->parent->left = temp;
	}
	else
	{
		node->parent->right = temp;
	}

	node->right = temp->left;
	temp->left = node;
	node->parent = temp;
}
template <class Value, class Key>
void Map<Value, Key>::rotateRight(Node* node)
{
	Node* temp = node->left;
	node->left = temp->right;

	if(temp->right != 0x0)
	{
		temp->right->parent = node;
	}

	temp->parent = node->parent;
	if(node->parent == 0x0)
	{
		this->root = temp;
	}
	else if(node == node->parent->right)
	{
		node->parent->right = temp;
	}
	else
	{
		node->parent->left = temp;
	}

	node->left = temp->right;
	temp->right = node;
	node->parent = temp;
}

template <class Value, class Key>
void Map<Value, Key>::recursiveCopy(Node* thisNode, Node* origNode)
{
	Node* currentThis = thisNode;
	Node* currentOrig = origNode;
	BasicList<typename Map<Value, Key>::Node*> stackThis;
	BasicList<typename Map<Value, Key>::Node*> stackOrig;

	stackThis.pushBack(currentThis);
	stackOrig.pushBack(currentOrig);
	while(currentOrig->left != NULL)
	{
		Node* newNode = new Node(currentOrig->left->value, currentOrig->left->key, currentOrig->left->red);
		newNode->parent = currentThis;
		currentThis->left = newNode;

		currentThis = currentThis->left;
		currentOrig = currentOrig->left;

		stackThis.pushBack(currentThis);
		stackOrig.pushBack(currentOrig);
	}

	while(stackOrig.size() > 0)
	{
		currentThis = stackThis.popBack();
		currentOrig = stackOrig.popBack();

		if(currentOrig->right != 0x0)
		{
			Node* newNode = new Node(currentOrig->right->value, currentOrig->right->key, currentOrig->right->red);
			newNode->parent = currentThis;
			currentThis->right = newNode;

			currentThis = currentThis->right;
			currentOrig = currentOrig->right;
			while(currentOrig != 0x0)
			{
				if(currentOrig->left != 0x0)
				{
					Node* newNode = new Node(currentOrig->left->value, currentOrig->left->key, currentOrig->left->red);
					newNode->parent = currentThis;
					currentThis->left = newNode;
				}

				stackThis.pushBack(currentThis);
				stackOrig.pushBack(currentOrig);
				currentThis = currentThis->left;
				currentOrig = currentOrig->left;
			}
		}
	}
}

template <class Value, class Key>
void Map<Value, Key>::recursiveRemove(Node* current)
{
	BasicList<typename Map<Value, Key>::Node*> stack;

	if(current == NULL)
		return;

	stack.pushBack(current);
	while(current->left != NULL)
	{
		current = current->left;
		stack.pushBack(current);
	}

	while(stack.size() > 0)
	{
		current = stack.popBack();

		if(current->right != NULL)
		{
			Node* temp = current->right;
			while(temp != NULL)
			{
				stack.pushBack(temp);
				temp = temp->left;
			}
		}

		delete current;
	}
}

/////////////////////////////////////////////////////////////////////
/////////////////////////// Iterators ///////////////////////////////
/////////////////////////////////////////////////////////////////////

template <class Value, class Key>
class Map<Value, Key>::InOrderIterator
{
public:
	InOrderIterator(Map<Value, Key>* tree)
	{
		this->current = tree->root;

		if(this->current == NULL)
			return;

		this->stack.pushBack(this->current);
		while(this->current->left != NULL)
		{
			this->current = this->current->left;
			this->stack.pushBack(this->current);
		}
		(*this)++;
	}
	InOrderIterator(const InOrderIterator& it)
	{
		this->current = it.current;
		this->stack = it.stack;
	}

	Key key()
	{
		return current->key;
	}
	Value value()
	{
		return current->value;
	}

	bool operator!()
	{
		if(current != NULL)
			return true;
		else
			return false;
	}
	void operator++(int)
	{
		if(stack.size() > 0)
		{
			current = stack.popBack();

			if(current->right != NULL)
			{
				Node* temp = current->right;
				while(temp->left != NULL)
				{
					stack.pushBack(temp);
					temp = temp->left;
				}
				stack.pushBack(temp);
			}
		}
		else
		{
			current = NULL;
		}
	}
private:
	typename Map<Value, Key>::Node* current;
	BasicList<typename Map<Value, Key>::Node*> stack;
};

template <class Value, class Key>
class Map<Value, Key>::DepthFirstIterator
{
public:
	DepthFirstIterator(Map<Value, Key>* tree)
	{
		this->stack.pushBack(tree->root);
		(*this)++;
	}
	DepthFirstIterator(const DepthFirstIterator& orig)
	{
		this->current = orig.current;
		this->stack = orig.stack;
	}

	Key key()
	{
		return current->key;
	}
	Value value()
	{
		return current->value;
	}

	bool operator!()
	{
		if(current != NULL)
			return true;
		else
			return false;
	}
	void operator++(int)
	{
		if(stack.size() > 0)
		{
			current = stack.popBack();
		}
		else
		{
			current = NULL;
			return;
		}

		if(current->right != 0x0)
		{
			stack.pushBack(current->right);
		}
		if(current->left != 0x0)
		{
			stack.pushBack(current->left);
		}
	}

private:
	typename Map<Value, Key>::Node* current;
	BasicList<typename Map<Value, Key>::Node*> stack;
};

template <class Value, class Key>
class Map<Value, Key>::BreadthFirstIterator
{
public:
	BreadthFirstIterator(Map<Value, Key>* tree)
	{
		this->queue.pushBack(tree->root);
		(*this)++;
	}
	BreadthFirstIterator(const BreadthFirstIterator& orig)
	{
		this->current = orig.current;
		this->queue = orig.queue;
	}

	Key key()
	{
		return current->key;
	}
	Value value()
	{
		return current->value;
	}

	bool operator!()
	{
		if(current != 0x0)
			return true;
		else
			return false;
	}
	void operator++(int)
	{
		if(queue.size() <= 0)
		{
			current = 0x0;
		}
		else
		{
			current = queue.popFront();
			if(current->left != 0x0)
				queue.pushBack(current->left);
			if(current->right != 0x0)
				queue.pushBack(current->right);
		}
	}

private:
	BasicList<typename Map<Value, Key>::Node*> queue;
	typename Map<Value, Key>::Node* current;
};

template <class Value, class Key>
typename Map<Value, Key>::Iterator Map<Value, Key>::begin()
{
	return Iterator(this);
}
template <class Value, class Key>
typename Map<Value, Key>::InOrderIterator Map<Value, Key>::beginInOrder()
{
	return InOrderIterator(this);
}
template <class Value, class Key>
typename Map<Value, Key>::DepthFirstIterator Map<Value, Key>::beginDepthFirst()
{
	return DepthFirstIterator(this);
}
template <class Value, class Key>
typename Map<Value, Key>::BreadthFirstIterator Map<Value, Key>::beginBreadthFirst()
{
	return BreadthFirstIterator(this);
}

#endif
