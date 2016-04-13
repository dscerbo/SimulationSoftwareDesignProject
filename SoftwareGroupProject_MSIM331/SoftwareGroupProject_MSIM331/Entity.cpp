#include "Entity.h"

int Entity::_nextID = 1;

Entity::Entity()
{
	_id = _nextID++;
}

int Entity::GetID()
{
	return _id;
}
