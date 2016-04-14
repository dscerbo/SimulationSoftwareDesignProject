#pragma once
#include "Simulation.h"

class Message
{
public:
	Message();
	int GetID();
	Message *New()
	{
		return new Message();
	}
	void UpdateMessageWaitTime(Time **waitTimes); 
	Time **UpdateNodeWaitTime(); 
	int GetLastNode(); 
	void UpdateLastNode(int LastNode); 
	~Message();

private:
	int _LastNode; 
	Time TimeSpentWaiting; 
	Time TimeCreated;
	int _id;
	static int _nextID;
	Time **_waitTimes; 
};
