#pragma once

#include "Message.h"
#include "FIFO.h"
#include "Distribution.h"

class Node : public SimObj
{
public:
	Node(int ID, Distribution *serviceTime, Distribution *generationRate, int **adjacencyMatrix, int numVertices, int numEdges);
	void ScheduleArrivalIn(Time deltaT, Message *message);
	void ScheduleArrivalAt(Time time, Message *message);

private:
	int _ID;
	int _numEdges;
	int _numVertices;
	Distribution *_serviceTime;
	Distribution *_generationRate;
	int **_adjacencyMatrix; //Reference to the adjacency matrix
	static Time **_waitTimes;
	int _numMsgs;

	enum ServerState { busy, idle };
	ServerState _state;
	FIFO<Message> *_queues;
	int currentQueue; 
	class ArriveEvent;
	class ServeEvent;
	class DepartEvent;
	class NextMessageEvent;
	void Arrive(Message *message);
	void Serve();
	void NextMessage();

	//Depart needs to determine next vertex
	void Depart(Message *message);
	int DetermineNextNode(Message *message); 
};
