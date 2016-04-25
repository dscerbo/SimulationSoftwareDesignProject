#include "Message.h"

int Message::_nextID = 1;

Message::Message(int destination)
{
	_id = _nextID++;
	_destination = destination;
	_TimeCreated = GetCurrentSimTime();
	TimeSpentWaiting = 0; 
}

Message::~Message()
{

}

int Message::GetID()
{
	return _id;
}

//void Message::UpdateMessageWaitTime(Time **waitTimes) {
//	_waitTimes = waitTimes; 
//}
//
//Time **Message::UpdateNodeWaitTime() {
//	return _waitTimes; 
//}

int Message::GetLastNode() {
	return _LastNode; 
}

void Message::UpdateLastNode(int LastNode) {
	_LastNode = LastNode; 
}

int Message::GetDestination() {
	return _destination; 
}

void Message::UpdateEnteredQueue() {
	_enteredQueue = GetCurrentSimTime();
}


void Message::UpdateTimeSpentWaiting() {
	TimeSpentWaiting += (GetCurrentSimTime() - _enteredQueue);
}

Time Message::GetTimeSpentWaiting() {
	return TimeSpentWaiting;
}

void Message::OutputStatistics(std::ofstream& outFile) {
	Time communicationTime = GetCurrentSimTime() - _TimeCreated;
	outFile << "Message: " << _id << std::endl
		<< "Communication Time: " << communicationTime << std::endl
		<< "Wait Time: " << TimeSpentWaiting << std::endl;
}
