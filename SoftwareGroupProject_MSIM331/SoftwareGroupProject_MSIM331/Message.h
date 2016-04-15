#pragma once
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
	int GetLastNode(); 
	void UpdateLastNode(int LastNode); 
	~Message();

private:
	int _LastNode;
	Time TimeSpentWaiting;
	Time _TimeCreated;
	int _id;
	int _destination;
	static int _nextID;
	//Time **_waitTimes; 
};
