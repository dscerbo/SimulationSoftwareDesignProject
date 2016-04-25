#include "Node.h"
#include <limits>

class Node::NextMessageEvent : public Event
{
public:
	NextMessageEvent(Node *node) { _node = node; }
	void Execute()
	{
		_node->NextMessage();
	}
private:
	Node *_node;
};

void Node::NextMessage()
{
	if ((_numMsgs == -1) || (_numMsgs > 0))
	{
		if (_numMsgs > 0) 
			_numMsgs--;
		int randomNode = (_ID + (rand() % _numVertices - 1) + 1) % _numVertices;
		Message *msg = new Message(randomNode);
		msg->UpdateLastNode(-1);
		cout << GetCurrentSimTime() << ", " << _ID << ", NextMessage, Message " << msg->GetID() << ", Destination " << randomNode << endl;
		this->ScheduleArrivalIn(0, msg);
		ScheduleEventIn(_generationRate->GetRV(), new NextMessageEvent(this));
	}
}

Node::Node(int ID, Distribution *serviceTime, Distribution *generationRate, int **adjacencyMatrix, int numVertices, int numEdges, std::ofstream& outfile)
{
	_outFile = &outfile;
	_ID = ID;
	_numEdges = numEdges; 
	_numVertices = numVertices; 
	currentQueue = 0; 
	_state = idle;
	_serviceTime = serviceTime;
	_generationRate = generationRate;
	_adjacencyMatrix = adjacencyMatrix; 
	_waitTimes = new Time*[numVertices]; 
	_serverReserved = false;
	for (int i = 0; i < numVertices; i++) {
		_waitTimes[i] = new Time[numVertices];
	}
	for (int i = 0; i < numVertices; i++) {
		for (int j = 0; j < numVertices; j++) {
			_waitTimes[i][j] = 0; //Initialize all wait times to 0
		}
	}

	_numMsgs = 5; //For now
	messagesInQueue = 0;
	maxQueueSize = 0;
	processingTime = 0; 
	numArrivedMessages = 0; 
	totalWaitTime = 0; 

	//Declare FIFO queue IDs
	_queues = new FIFO<Message>[numEdges + 1];
	int counter = 1; 
	_queues[0].SetID(_ID); //Internal Queue

	for (int i = 0; i < numVertices; i++) {
		if (adjacencyMatrix[_ID][i] == 1) {
			_queues[counter].SetID(i); //Income Queues
			counter++;
		} 
	}

	//Create First entity
	ScheduleEventIn(0.0, new NextMessageEvent(this));

	neighors = new Node*[numVertices];

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
	cout << GetCurrentSimTime() << ", SSSQ " << _ID << ", Arrive, Message " << message->GetID() << endl;
	//count nmber of messages and then update current wait time at the node
	messagesInQueue++;
	numArrivedMessages++; 
	if (messagesInQueue > maxQueueSize) {
		maxQueueSize = messagesInQueue;
	}
	_waitTimes[_ID][0] += _serviceTime->GetMean();
	_waitTimes[_ID][1] = GetCurrentSimTime();

	//Update last node
	//Add entity to the correct queue
	if (message->GetLastNode() == -1)
		_queues[0].AddEntity(message); //Add to Internal Queue
	else
	{
		for (int i = 1; i <= _numEdges; i++) 
		{
			if (_queues[i].GetID() == message->GetLastNode()) 
			{
				_queues[i].AddEntity(message);
				break;
			}
		}
	}

	message->UpdateLastNode(_ID);
	message->UpdateEnteredQueue();

	if ((_state == idle) && (!_serverReserved)) 
	{
		ScheduleEventIn(0, new ServeEvent(this));
		_serverReserved = true;
	}

	//Update the newest wait times ----Not worrying about wait times right now-----
	/*for (int i = 0; i < _numEdges; i++) {
	if (message->UpdateNodeWaitTime()[i][1] > _waitTimes[i][1])
	_waitTimes[i] = message->UpdateNodeWaitTime()[i];
	_waitTimes[i] = message->UpdateNodeWaitTime()[i];
	}*/
}

void Node::ScheduleArrivalAt(Time time, Message *message)
{
	ScheduleEventAt(time, new ArriveEvent(this, message));
}

void Node::ScheduleArrivalIn(Time deltaT, Message *message)
{
	ScheduleEventIn(deltaT, new ArriveEvent(this, message));
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
	while (_queues[currentQueue].IsEmpty() == true) {
		currentQueue = (currentQueue + 1) % (_numEdges + 1); 
	}
	Message *message = _queues[currentQueue].GetEntity();
	totalWaitTime += message->GetTimeSpentWaiting();
	messagesInQueue--;
	message->UpdateTimeSpentWaiting();
	cout << GetCurrentSimTime() << ", SSSQ " << _ID << ", Serve, Message " << message->GetID() << endl;
	_state = busy;
	_serverReserved = false;
	Time serviceTime = _serviceTime->GetRV();
	processingTime += serviceTime;
	ScheduleEventIn(serviceTime, new DepartEvent(this, message));
}

void Node::Depart(Message *message)
{
	_waitTimes[_ID][0] -= _serviceTime->GetMean();
	_waitTimes[_ID][1] = GetCurrentSimTime();

	_state = idle;

	if (message->GetDestination() == _ID)
		Sink(message);

	else
	{
		cout << GetCurrentSimTime() << ", Node " << _ID << ", Depart, Message " << message->GetID();
		neighors[DetermineNextNode(message)]->Arrive(message);
		
	}

	for (int i = 0; i <= _numEdges; i++) {
		if (!(_queues[currentQueue].IsEmpty()) && (!_serverReserved))
		{
			ScheduleEventIn(0, new ServeEvent(this));
			_serverReserved = true;
		}
		currentQueue = (currentQueue + 1) % (_numEdges + 1);
	}
}

int Node::DetermineNextNode(Message *message)
{
	double *distance = new double[_numVertices];
	bool *pathFinalized = new bool[_numVertices];
	int *parent = new int[_numVertices];
	for (int i = 0; i < _numVertices; i++) {
		distance[i] = INT_MAX; 
		pathFinalized[i] = false;
	}
	parent[_ID] = -1;
	distance[_ID] = 0; 
	for (int i = 0; i < _numVertices - 1; i++) {
		double min = INT_MAX;
		int min_index; 
		//Determine 
		for (int j = 0; j < _numVertices; j++) {
			if (pathFinalized[j] == false && distance[j] <= min)
				min = distance[j], min_index = j;
		}
		pathFinalized[min_index] = true;
		for (int j = 0; j < _numVertices; j++) {
			if (!pathFinalized[j] && _adjacencyMatrix[min_index][j] != 0
				&& distance[min_index] != INT_MAX
				&& distance[min_index] + *_waitTimes[j] <= distance[j])
			{
				parent[j] = min_index;
				distance[j] = distance[min_index] + *_waitTimes[j];
			}
		}
	}

	int nextNode = message->GetDestination();
	while (parent[parent[nextNode]] != -1) {
		nextNode = parent[nextNode];
	}

	std::cout << ", Destination: " << nextNode << endl;
	return nextNode;
}

Time** Node::_waitTimes = new Time*[2];

void Node::Sink(Message *message)
{
	cout << GetCurrentSimTime() << ", Node " << _ID << ", Sink, Message " << message->GetID() << endl;
	message->OutputStatistics(*_outFile);
	delete message;
}

void Node::SetNeighbor(int ID, Node *neighborVertex)
{
	neighors[ID] = neighborVertex;
}

void Node::OutputStatistics() {
	Time AverageProcessingTime = processingTime / numArrivedMessages;
	Time Efficency = processingTime / GetCurrentSimTime();
	Time AverageWaitTime = totalWaitTime / numArrivedMessages;
	*_outFile << "Node: " << _ID << endl
		<< "Average Processing Time: " << AverageProcessingTime << endl
		<< "Efficency: " << Efficency << endl
		<< "Average Wait Time: " << AverageWaitTime << endl;
}