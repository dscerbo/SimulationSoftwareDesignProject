#include "Message.h"

int Message::_nextID = 1;

Message::Message()
{
	_id = _nextID++;
}

Message::~Message()
{

}

int Message::GetID()
{
	return _id;
}

