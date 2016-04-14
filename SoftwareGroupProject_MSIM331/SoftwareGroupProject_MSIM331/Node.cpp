#include "Node.h"

Node::Node(int ID, Distribution *serviceTime, Distribution *generationRate, int **adjacencyMatrix, int numVertices, int numEdges)
{
	_ID = ID;
	_numEdges = numEdges; 
	currentQueue = 0; 
	_state = idle;
	_serviceTime = serviceTime;
	_generationRate = generationRate;
	_adjacencyMatrix = adjacencyMatrix; 
	_waitTimes = new Time*[numVertices];
	//Declare wait time array [i][0] is wait time, [i][0] is time when defined
	for (int i = 0; i < numVertices; ++i) {
		_waitTimes[i] = new Time[2];
		_waitTimes[numVertices][0] = _waitTimes[numVertices][1] = 0.0;
	}
	//Declare FIFO queue IDs
	for (int i = 0, int j = 1; i < numVertices; i++) {
		if (adjacencyMatrix[_ID][i] = 1) {
			_queues[j] = new FIFO<Message>(_ID);
			j++;
		} 
	}
}

class Node::Source : public SimObj
{
public:
	Source(int sourceNode, Node *node, Distribution *generation);
	Source(int sourceNode, Node *node, Distribution *generation, int numMsgs);
private:
	class NextMessageEvent;
	Node* _node;
	Distribution* _generation;
	int _sourceNode;
	void NextMessage();
	int _numMsgs;
};


class Node::Source::NextMessageEvent : public Event
{
public:
	NextMessageEvent(Source *source) { _source = source; }
	void Execute()
	{
		_source->NextMessage();
	}
private:
	Source *_source;
};

Node::Source::Source(int sourceNode, Node * node, Distribution * generation)
{
	_sourceNode = sourceNode;
	_node = node;
	_generation = generation;
}

Node::Source::Source(int sourceNode, Node *node, Distribution *generation, int numMsgs)
{
	_sourceNode = sourceNode;
	_node = node;
	_generation = generation;
	_numMsgs = numMsgs;
}

void Node::Source::NextMessage()
{
	if ((_numMsgs == -1) || (_numMsgs > 0))
	{
		if (_numMsgs > 0) _numMsgs--;
		Message *msg = new Message;
		_node->ScheduleArrivalIn(0, msg);
		ScheduleEventIn(_generation->GetRV(), new NextMessageEvent(this));
	}
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
	//Add entity to the correct queue
	for (int i = 1; i <= _numEdges; i++) {
		if (_queues[i]->GetID() == message->GetLastNode) {
			_queues[i]->AddEntity(message);
			break; 
		}
	}

	//Update the newest wait times
	for (int i = 0; i < _numEdges; i++) {
		if (message->UpdateNodeWaitTime()[i][1] > _waitTimes[i][1])
			_waitTimes[i] = message->UpdateNodeWaitTime()[i];
			_waitTimes[i] = message->UpdateNodeWaitTime()[i];
	}

	if ((_state == idle)) {
		for (int i = 0; i <= _numEdges; i++) {
			if (_queues[i]->IsEmpty() == false)
				currentQueue = _queues[i]->GetID();
		}
		ScheduleEventIn(0, new ServeEvent(this));
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
	Message *message = _queues[currentQueue]->GetEntity();
	cout << GetCurrentSimTime() << ", SSSQ " << _ID << ", Serve, Entity " << message->GetID() << endl;
	_state = busy;
	ScheduleEventIn(_serviceTime->GetRV(), new DepartEvent(this, message));
}


void Node::Depart(Message *message)
{
	cout << GetCurrentSimTime() << ", SSSQ " << _ID << ", Depart, Entity " << message->GetID() << endl;

	_sink->Arrive(message); //Determine Next Node

	_state = idle;
	for (int i = 0; i <= _numEdges; i++) {
		if (!(_queues[currentQueue]->IsEmpty())) {
			ScheduleEventIn(0, new ServeEvent(this));
		}
		currentQueue = (currentQueue + 1) % (_numEdges + 1);
	}
	
}
