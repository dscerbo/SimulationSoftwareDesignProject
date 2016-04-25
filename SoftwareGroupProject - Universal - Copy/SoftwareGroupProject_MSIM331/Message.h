#pragma once
#include <fstream>
#include <iostream>
#include "Simulation.h"

class Message
{
public:
	Message(int destination);
	Message *New(int destination)
	{
		return new Message(destination);
	}
	int GetID();
	//void UpdateMessageWaitTime(Time **waitTimes); 
	//Time **UpdateNodeWaitTime(); 
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
	//Time **_waitTimes; 
};
