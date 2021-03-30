#pragma once
#ifndef RBTREEMAP_H
#define RBTREEMAP_H

#include <iostream>
#include <string>
#include "queue.h"

template <typename keyT, typename valueT>
class rbTreeMap
{
public:

	rbTreeMap()
	{
		nil = new rbNode<keyT, valueT>;
		nil->color = black; // Initialising the only important property of nil, which is color
		root = nil;
		size = 0;
	}

	// Assistant function used for restoring our tree's red-black property after insertion/deletion
	void leftRotate(rbNode<keyT, valueT> *x)
	{
		rbNode<keyT, valueT> *y = x->right; // Getting y
		x->right = y->left; // Reassigning x's right child

		if (y->left != nil) // If y's left child is not nil then we assign x as y's left child's parent
			y->left->parent = x;

		y->parent = x->parent;

		if (x->parent == nil) // If x does not have a parent then we set it to be the root
			root = y;
		else // Otherwise we set y as the appropriate child of x's parent
		{
			if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
		}

		// Setting x as y's left child
		y->left = x;
		x->parent = y;
	}

	// Assistant function used for restoring our tree's red-black property after insertion/deletion
	void rightRotate(rbNode<keyT, valueT> *y)
	{
		rbNode<keyT, valueT> *x = y->left; // Getting x
		y->left = x->right; // Reassigning y's left child

		if (x->right != nil) // If x's right child is not nil then we assign y as x's right child's parent
			x->right->parent = y;

		x->parent = y->parent;

		if (y->parent == nil) // If y does not have a parent then we set it to be the root
			root = x;
		else // Otherwise we set x as the appropriate child of x's parent
		{
			if (y == y->parent->right)
				y->parent->right = x;
			else
				y->parent->left = x;
		}

		// Setting y as x's right child
		x->right = y;
		y->parent = x;
	}
	
	// Assistant function for 'insert' which restores the red-black property for our tree
	void insertFix(rbNode<keyT, valueT> *z)
	{
		rbNode<keyT, valueT> *y; // z's uncle
		while (z->parent->color == red)
		{
			if (z->parent == z->parent->parent->left) // If z's parent is the left child of z's grandparent then
			{
				y = z->parent->parent->right;
				if (y->color == red) // Case 1
				{
					z->parent->color = black;
					y->color = black;
					z->parent->parent->color = red;
					z = z->parent->parent;
				}
				else
				{
					if (z == z->parent->right) // Case 2
					{
						z = z->parent;
						leftRotate(z);
					}
					else // Case 3
					{
						z->parent->color = black;
						z->parent->parent->color = red;
						rightRotate(z->parent->parent);
					}
				}
			}
			else
			{
				y = z->parent->parent->left;
				if (y->color == red) // Case 1
				{
					z->parent->color = black;
					y->color = black;
					z->parent->parent->color = red;
					z = z->parent->parent;
				}
				else
				{
					if (z == z->parent->left) // Case 2
					{
						z = z->parent;
						rightRotate(z);
					}
					else // Case 3
					{
						z->parent->color = black;
						z->parent->parent->color = red;
						leftRotate(z->parent->parent);
					}
				}
			}
		}

		root->color = black;
	}

	// Inserts a node with key 'key' and value 'value'
	void insert(keyT key, valueT value)
	{
		try
		{
			rbNode<keyT, valueT> *z = new rbNode<keyT, valueT>; // New node
			z->key = key;
			z->value = value;

			// Initialising helper nodes for insertion
			rbNode<keyT, valueT> *y = nil;
			rbNode<keyT, valueT> *x = root;

			while (x != nil) // BST Insertion
			{
				y = x;
				if (z->key < x->key)
					x = x->left;
				else if (z->key > x->key)
					x = x->right;
				else
					throw std::domain_error("ERROR: Can't insert a value that is already in the tree!");
			}

			// Deciding which child the new node will be
			z->parent = y;
			if (y == nil)
				root = z;
			else if (z->key < y->key)
				y->left = z;
			else
				y->right = z;

			// Initialising new nide's pointers and color
			z->left = nil;
			z->right = nil;
			z->color = red;

			size++; // Increasing the size variable
			insertFix(z); // Restoring the red-black tree property
		}
		catch (std::exception const &e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	// Assistant function for 'remove'
	void transplant(rbNode<keyT, valueT> *u, rbNode<keyT, valueT> *v)
	{
		if (u->parent == nil)
			root = v;
		else if (u == u->parent->left)
			u->parent->left = v;
		else
			u->parent->right = v;
		v->parent = u->parent;
	}

	// Assistant function for 'remove'
	rbNode<keyT, valueT> *tMin(rbNode<keyT, valueT> *x)
	{
		while (x->left != nil)
			x = x->left;
		return x;
	}

	// Assistant function for 'remove' which restores the red-black property for our tree
	void removeFix(rbNode<keyT, valueT> *x)
	{
		rbNode<keyT, valueT> *w;
		while (x != root && x->color == black)
		{
			if (x == x->parent->left)
			{
				w = x->parent->right;

				if (w->color == red) // Case 1
				{
					w->color = black;
					x->parent->color = red;
					leftRotate(x->parent);
					w = x->parent->right;
				}

				if (w->left->color == black && w->right->color == black) // Case 2
				{
					w->color = red;
					x = x->parent;
				}
				else if (w->right->color == black) // Case 3
				{
					w->left->color = black;
					w->color = red;
					rightRotate(w);
					w = x->parent->right;
				}
				else // Case 4
				{
					w->color = x->parent->color;
					x->parent->color = black;
					w->right->color = black;
					leftRotate(x->parent);
					x = root;
				}
			}
			else
			{
				w = x->parent->left;

				if (w->color == red) // Case 1
				{
					w->color = black;
					x->parent->color = red;
					rightRotate(x->parent);
					w = x->parent->left;
				}

				if (w->left->color == black && w->right->color == black) // Case 2
				{
					w->color = red;
					x = x->parent;
				}
				else if (w->left->color == black) // Case 3
				{
					w->right->color = black;
					w->color = red;
					leftRotate(w);
					w = x->parent->left;
				}
				else // Case 4
				{
					w->color = x->parent->color;
					x->parent->color = black;
					w->left->color = black;
					rightRotate(x->parent);
					x = root;
				}
			}
		}
		x->color = black;
	}

	// Removes a node with the 'key' key
	void remove(keyT key)
	{
		try
		{
			// Finding the node to be removed
			rbNode<keyT, valueT> *z = nil;
			rbNode<keyT, valueT> *cur = root;
			while (cur != nil && cur->key != key)
			{
				if (key < cur->key)
					cur = cur->left;
				else
					cur = cur->right;
			}
			z = cur;

			if (z == nil)
				throw std::domain_error("ERROR: Can't remove an element that is not in the tree!");

			rbNode<keyT, valueT> *x;
			rbNode<keyT, valueT> *y = z;
			clrs yOrigClr = y->color;

			if (z->left == nil) // z has 1 left child
			{
				x = z->right;
				transplant(z, z->right);
			}
			else if (z->right == nil) // z has 1 right child
			{
				x = z->left;
				transplant(z, z->left);
			}
			else // z has 2 children
			{
				y = tMin(z->right);
				yOrigClr = y->color;
				x = y->right;

				if (y->parent == z)
					x->parent = y;
				else
				{
					transplant(y, y->right);
					y->right = z->right;
					y->right->parent = y;
				}

				transplant(z, y);
				y->left = z->left;
				y->left->parent = y;
				y->color = z->color;
			}

			delete z;
			if (yOrigClr == black)
				removeFix(x);
		}
		catch (std::exception const &e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	// Returns an array of keys in breadth-traversal order
	int *getKeys()
	{
		queue<keyT, valueT> q;
		q.enqueue(root);

		size_t k = 0;
		int *arr = new int[size];

		rbNode<keyT, valueT> *v;
		while (!q.empty())
		{
			v = q.peek();
			q.dequeue();
			arr[k] = v->key;
			k++;

			if (v->left != nil)
				q.enqueue(v->left);
			if (v->right != nil)
				q.enqueue(v->right);
		}

		return arr;
	}

	// Returns an array of values in breadth-traversal order
	valueT *getValues()
	{
		queue<keyT, valueT> q;
		q.enqueue(root);

		size_t k = 0;
		std::string *arr = new std::string[size];

		rbNode<keyT, valueT> *v;
		while (!q.empty())
		{
			v = q.peek();
			q.dequeue();
			arr[k] = v->value;
			k++;

			if (v->left != nil)
				q.enqueue(v->left);
			if (v->right != nil)
				q.enqueue(v->right);
		}

		return arr;
	}

	// Clears the tree
	void clear()
	{
		queue<keyT, valueT> q;
		q.enqueue(root);

		rbNode<keyT, valueT> *v;
		while (!q.empty())
		{
			v = q.peek();
			q.dequeue();

			if (v->left != nil)
				q.enqueue(v->left);
			if (v->right != nil)
				q.enqueue(v->right);

			delete v;
		}
		root = nil;
	}

	// Prints the elements out in the console in breadth-traversal order
	void print()
	{
		queue<keyT, valueT> q;
		q.enqueue(root);

		rbNode<keyT, valueT> *v;
		while (!q.empty())
		{
			v = q.peek();
			q.dequeue();
			std::cout << v->key << " ";

			if (v->left != nil)
				q.enqueue(v->left);
			if (v->right != nil)
				q.enqueue(v->right);
		}
	}

	// Returns true if an element with key 'key' has been found
	bool find(keyT key)
	{
		rbNode<keyT, valueT> *cur = root;
		while (cur != nil)
		{
			if (key < cur->key)
				cur = cur->left;
			else if (key > cur->key)
				cur = cur->right;
			else
				return true;
		}
		return false;
	}

	// Returns the value of element with key 'key' or throws an exception if it doesn't find one
	valueT findAndReturn(keyT key)
	{
		try
		{
			rbNode<keyT, valueT> *cur = root;
			while (cur != nil)
			{
				if (key < cur->key)
					cur = cur->left;
				else if(key > cur->key)
					cur = cur->right;
				else
					return cur->value;
			}
			throw std::domain_error("ERROR: Couldn't find the node");
		}
		catch (std::exception const &e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	// Returns true if the tree is empty
	bool empty()
	{
		if (root != nil)
			return false;
		else
			return true;
	}

	~rbTreeMap()
	{
		if (!empty())
			clear();
		delete nil;
	}

	size_t getSize()
	{
		return size;
	}

private:
	rbNode<keyT, valueT> *root;
	rbNode<keyT, valueT> *nil;
	size_t size;
};
#endif