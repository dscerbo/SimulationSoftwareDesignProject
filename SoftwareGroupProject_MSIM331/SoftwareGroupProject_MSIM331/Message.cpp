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

void Message::UpdateMessageWaitTime(Time **waitTimes) {
	_waitTimes = waitTimes; 
}

Time **Message::UpdateNodeWaitTime() {
	return _waitTimes; 
}

int Message::GetLastNode() {
	return _LastNode; 
}

void Message::UpdateLastNode(int LastNode) {
	_LastNode = LastNode; 
}