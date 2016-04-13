#pragma once

#include "Simulation.h"

class Entity
{
public:
	Entity();
	int GetID();
private:
	int _id;
	static int _nextID;
};
