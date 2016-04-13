#pragma once

#include "Message.h"
#include "FIFO.h"

class Node : public SimObj
{
public:
	Node(int ID, Node *neighbors);

private:
	int _ID;
	FIFO<Message> *_queues; 
};

Node::Node(int ID, Node *neighbors)
{
	_ID = ID; 
}
