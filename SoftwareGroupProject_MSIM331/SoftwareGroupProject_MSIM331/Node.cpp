#include "Node.h"

Node::Node(int ID, Distribution *serviceTime, Distribution *generationRate, int *adjacencyMatrix)
{
	_ID = ID;
	_state = idle;
	_serviceTime = serviceTime;
	_generationRate = generationRate;
	_adjacencyMatrix = adjacencyMatrix; 

}

class Node::ArriveEvent : public Event
{
public:
	ArriveEvent(Node *node, Message *message)
	{
		_node = node;
		_message = message;
	}

	void Execute()
	{
		_node->Arrive(_message);
	}
private:
	Node *_node;
	Message *_message;
};

void Node::ScheduleArrivalAt(Time time, Message *message)
{
	ScheduleEventAt(time, new ArriveEvent(this, message));
}

void Node::ScheduleArrivalIn(Time deltaT, Message *message)
{
	ScheduleEventIn(deltaT, new ArriveEvent(this, message));
}

class Node::ServeEvent : public Event
{
public:
	ServeEvent(Node *node)
	{
		_node = node;
	}

	void Execute()
	{
		_node->Serve();
	}

private:
	Node *_node;
};

void Node::Arrive(Message *message)
{
	cout << GetCurrentSimTime() << ", SSSQ " << _ID << ", Arrive, Entity " << message->GetID() << endl;
	_queues->AddEntity(message);
	if ((_state == idle) && (!_serverReserved)) {
		ScheduleEventIn(0, new ServeEvent(this));
		_serverReserved = true;
	}
}

class Node::DepartEvent : public Event
{
public:
	DepartEvent(Node *node, Message *message)
	{
		_node = node;
		_message = message;
	}

	void Execute()
	{
		_node->Depart(_message);
	}
private:
	Node *_node;
	Message *_message;
};

void Node::Serve()
{
	Message *message = _queues->GetEntity();
	cout << GetCurrentSimTime() << ", SSSQ " << _ID << ", Serve, Entity " << message->GetID() << endl;
	_state = busy;
	_serverReserved = false;
	ScheduleEventIn(_serviceTime->GetRV(), new DepartEvent(this, message));
}


//Depart needs to determine next node to send to
void Node::Depart(Message *message)
{
	cout << GetCurrentSimTime() << ", SSSQ " << _ID << ", Depart, Entity " << message->GetID() << endl;
	_sink->Arrive(message); //Right here
	_state = idle;
	if (!(_queues->IsEmpty()) && (!_serverReserved)) {
		ScheduleEventIn(0, new ServeEvent(this));
		_serverReserved = true;
	}
}
