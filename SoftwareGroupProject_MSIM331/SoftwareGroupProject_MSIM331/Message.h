#pragma once
#include "Entity.h"

class Message : public Entity
{
public:
	Message();
	Entity *New()
	{
		return new Message(); 
	}
	~Message();

private:
	Time TimeSpentWaiting; 
	Time TimeCreated;
};



