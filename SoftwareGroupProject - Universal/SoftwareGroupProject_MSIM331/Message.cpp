#include "Message.h"

int Message::_nextID = 1;

Message::Message(int destination, int numVertices)
{
	_id = _nextID++;
	_destination = destination;
	_TimeCreated = GetCurrentSimTime();
	TimeSpentWaiting = 0;
	_waitTimes = new Time*[numVertices];
	for (int i = 0; i < numVertices; i++) {
		_waitTimes[i] = new Time[2];
		_waitTimes[i][0] = 0; 
		_waitTimes[i][1] = 0;
	}
}

Message::~Message()
{

}

int Message::GetID()
{
	return _id;
}

//void Message::UpdateMessageWaitTime(Time **waitTimes) {
//	for (int i = 0; i < _numVertices; i++) {
//		//If the internal wait time is older than the node's wait times
//		if (_waitTimes[i][1] < waitTimes[i][1]){
//			_waitTimes[i][1] = waitTimes[i][1];
//			_waitTimes[i][0] = waitTimes[i][1];
//		}
//	}
//}
//
//Time **Message::GetWaitTime() {
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
	return (GetCurrentSimTime() - _enteredQueue);
}

void Message::OutputStatistics(std::ofstream& outFile) {
	Time communicationTime = (GetCurrentSimTime() - _TimeCreated);
	outFile << "Message - " << _id << std::endl
		<< "Communication Time: " << communicationTime << std::endl
		<< "Wait Time: " << TimeSpentWaiting << std::endl;
}
