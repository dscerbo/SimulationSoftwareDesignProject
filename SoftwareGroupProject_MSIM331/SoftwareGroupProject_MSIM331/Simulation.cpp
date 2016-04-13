#include "Simulation.h"

// Event List definition
// Separate from simulation executive to facillitate replacing it

class SimObj::EventList
{
public:
	EventList()
	{
		_first = 0;
	};

	void AddEvent(Time time, Event *ev)
		//Add a new event to the event list
	{
		EventNode *en = new EventNode(time, ev);
		if (_first == 0) {
			_first = en;
		}
		else if (time < _first->_time) {
			en->_next = _first;
			_first = en;
		}
		else {
			EventNode *current = _first;
			while ((current->_next == 0) ? false : (current->_next->_time <= time)) {
				current = current->_next;
			}
			en->_next = current->_next;
			current->_next = en;
		}
	};

	Event *GetEvent()
		//Return the next event in the event list (base on simulation time)
	{
		Event *ev = _first->_ev;
		EventNode *en = _first;
		_first = _first->_next;
		//		delete en;
		return ev;
	};

	Time GetTime()
	{
		return _first->_time;
	};

	bool HasEvent()
	{
		return (_first != 0);
	};

private:
	struct EventNode
	{
		EventNode(Time time, Event *ev)
		{
			_time = time;
			_ev = ev;
			_next = 0;
		};
		Time _time;
		Event *_ev;
		EventNode *_next;
	};
	EventNode *_first;
};


// Event List definition
// Separate from simulation executive to facillitate replacing it
void RunSimulation()
{
	while (SimObj::_eventList.HasEvent()) {
		SimObj::_currentTime = SimObj::_eventList.GetTime();
		Event *ev = SimObj::_eventList.GetEvent();
		ev->Execute();
	}
}

void RunSimulation(Time endTime)
{
	while ((SimObj::_eventList.HasEvent()) ? (SimObj::_eventList.GetTime() <= endTime) : false) {
		SimObj::_currentTime = SimObj::_eventList.GetTime();
		Event *ev = SimObj::_eventList.GetEvent();
		ev->Execute();
	}
}

Time GetCurrentSimTime()
{
	return(SimObj::_currentTime);
}

Time SimObj::_currentTime = 0.0;
SimObj::EventList SimObj::_eventList;

SimObj::SimObj()
{
}

void SimObj::ScheduleEventIn(Time time, Event *ev)
{
	_eventList.AddEvent(_currentTime + time, ev);
}

void SimObj::ScheduleEventAt(Time time, Event *ev)
{
	_eventList.AddEvent(time, ev);
}
