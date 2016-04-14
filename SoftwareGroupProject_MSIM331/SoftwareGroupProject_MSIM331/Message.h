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
	~Message();

private:
	Time TimeSpentWaiting; 
	Time TimeCreated;
	int _id;
	static int _nextID;
};
