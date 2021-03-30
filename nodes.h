#ifndef NODES_H
#define NODES_H

#include <iostream>
#include <string>

enum clrs { red, black };

template <typename keyT, typename valueT>
class rbNode
{
public:
	keyT key;
	valueT value;

	rbNode *parent;
	rbNode *left;
	rbNode *right;

	clrs color;
};

// Node class for queue
template <typename keyT, typename valueT>
class node
{
public:
	rbNode<keyT, valueT> *data; // Basic data block
	node *link; // A pointer for linking queue

	node() // Basic node constructor
	{
		data = NULL;
		link = NULL;
	}
};

#endif