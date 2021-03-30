#pragma once
#ifndef QUEUE_H
#define QUEUE_H

#include "nodes.h"
//#include <fstream>

/*
	Queue:     Front             Rear
			   A1 -> A2 -> A3 -> A4
	Insert:    Front             Rear     Front                   Rear
			   A1 -> A2 -> A3 -> A4   =>  A1 -> A2 -> A3 -> A4 -> A5
	Delete:    Front                   Rear     Front             Rear
			   A1 -> A2 -> A3 -> A4 -> A5   =>  A2 -> A3 -> A4 -> A5
*/
template <typename keyT, typename valueT>
class queue
{
public:

	// Basic constructor
	queue()
	{
		front = NULL;
		rear = NULL;
		size_v = 0;
	}

	// Destructor
	~queue()
	{
		clear();
	}

	// Copy constructor
	queue(const queue &toCopy)
	{
		front = NULL;
		rear = NULL;
		size_v = 0;

		for (size_t i = 0; i < toCopy.size_v; i++)
			enqueue(0);

		node<keyT, valueT> *curR = toCopy.front;
		node<keyT, valueT> *curL = front;
		for (size_t i = 0; i < toCopy.size_v; i++)
		{
			curL->data = curR->data;
			curL = curL->link;
			curR = curR->link;
		}
	}

	// Enqueue
	void enqueue(rbNode<keyT, valueT> *data)
	{
		node<keyT, valueT> *temp = new node<keyT, valueT>;
		temp->data = data;

		if (!front)
		{
			front = temp;
			front->link = NULL;
		}
		else if (front && !rear)
		{
			rear = temp;
			front->link = rear;
			rear->link = NULL;
		}
		else
		{
			rear->link = temp;
			rear = temp;
			rear->link = NULL;
		}

		size_v++;
	}

	// Dequeue
	void dequeue()
	{
		if (!empty())
		{
			if (front && !rear)
			{
				delete front;
				front = NULL;
			}
			else if (front->link == rear)
			{
				delete front;
				front = rear;
				rear = NULL;
			}
			else
			{
				node<keyT, valueT> *temp = front->link;
				delete front;
				front = temp;
			}

			size_v--;
		}
	}

	// Check if queue is empty
	bool empty()
	{
		if (front)
			return false;
		else
			return true;
	}

	// Returns the size of the queue
	size_t size()
	{
		return size_v;
	}

	// Returns front element
	rbNode<keyT, valueT> *peek()
	{
		if (!empty())
			return front->data;
	}

	// Clears the queue
	void clear()
	{
		if (!empty())
		{
			size_t i = 0, s = size_v;
			while (i < s)
			{
				dequeue();
				i++;
			}
		}
	}

	// Prints all elements
	void print()
	{
		if (!empty())
		{
			node<keyT, valueT> *cur = front;
			while (cur->link != NULL)
			{
				std::cout << cur->data;
				cur = cur->link;
			}
		}
	}

private:
	// Front pointer
	node<keyT, valueT> *front;
	// Rear pointer
	node<keyT, valueT> *rear;
	// Size variable
	size_t size_v;
};
#endif