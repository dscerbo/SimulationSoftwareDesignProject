#pragma once

#include "Message.h"
#include "FIFO.h"
#include "Distribution.h"

class Node : public SimObj
{
public:
	Node(int ID, Distribution *serviceTime, Distribution *generationRate, int *adjacencyMatrix);
	void ScheduleArrivalIn(Time deltaT, Message *message);
	void ScheduleArrivalAt(Time time, Message *message);
private:
	int _ID;
	Distribution *_serviceTime;
	Distribution *_generationRate;
	int *_adjacencyMatrix; //Reference to the adjacency matrix. Need to define in the main
	
	enum ServerState { busy, idle };
	ServerState _state;
	FIFO<Message> *_queues;
	bool _serverReserved;
	class ArriveEvent;
	class ServeEvent;
	class DepartEvent;
	class Source;
	void Arrive(Message *message);
	void Serve();

	//Depart needs to determine next vertex
	void Depart(Message *message);
};
