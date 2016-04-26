#pragma once
#include <fstream>
#include <iostream>
#include "Simulation.h"

class Message
{
public:
	Message(int destination, int numVertices);
	Message *New(int destination, int numVertices)
	{
		return new Message(destination, numVertices);
	}
	int GetID();
	//void UpdateMessageWaitTime(Time **waitTimes); 
	//Time **GetWaitTime(); 
	void UpdateEnteredQueue();
	void UpdateTimeSpentWaiting();
	int GetLastNode(); 
	void UpdateLastNode(int LastNode); 
	int GetDestination();
	Time GetTimeSpentWaiting();
	void OutputStatistics(std::ofstream& outFile);
	~Message();

private:
	int _LastNode;
	Time TimeSpentWaiting;
	Time _TimeCreated;
	Time _enteredQueue;
	int _id;
	int _destination;
	static int _nextID;
	int _numVertices;
	Time **_waitTimes; 
};
