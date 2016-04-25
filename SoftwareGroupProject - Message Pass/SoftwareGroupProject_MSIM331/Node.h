#pragma once

#include "Message.h"
#include "FIFO.h"
#include "Distribution.h"

class Node : public SimObj
{
public:
	Node() {};
	Node(int ID, Distribution *serviceTime, Distribution *generationRate, int **adjacencyMatrix, int numVertices, int numEdges, std::ofstream& outFile);
	void ScheduleArrivalIn(Time deltaT, Message *message);
	void ScheduleArrivalAt(Time time, Message *message);
	void SetNeighbor(int ID, Node *neighborVertex);
	void OutputStatistics();

private:
	int _ID;
	int _numEdges;
	int _numVertices;
	Distribution *_serviceTime;
	Distribution *_generationRate;
	bool _serverReserved;
	int **_adjacencyMatrix; //Reference to the adjacency matrix
	Time **_waitTimes; //[0] is wait time [1] is when time was taken
	int _numMsgs;
	int currentQueue; 
	Node **neighors;
	int messagesInQueue;
	int maxQueueSize;
	Time processingTime;
	int numArrivedMessages;
	Time totalWaitTime;
	std::ofstream *_outFile;

	enum ServerState { busy, idle };
	ServerState _state;
	FIFO<Message> *_queues;

	class ArriveEvent;
	class ServeEvent;
	class DepartEvent;
	class NextMessageEvent;
	void Arrive(Message *message);
	void Serve();
	void NextMessage();
	void Sink(Message *message);

	//Depart needs to determine next vertex
	void Depart(Message *message);
	int DetermineNextNode(Message *message); 
};
