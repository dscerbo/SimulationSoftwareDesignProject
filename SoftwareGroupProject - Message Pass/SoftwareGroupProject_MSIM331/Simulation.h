#pragma once

typedef double Time;

class Event
{
public:
	Event() {};
	virtual void Execute() = 0;
};

Time GetCurrentSimTime();
/*
	GetCurrentSimTime
		Parameters:
			none
		Return value:
			Current simulation time.
		Behavior:
			Returns the simulation time of the currently executing event.
*/

void RunSimulation();
/*
	RunSimulation
		Parameters:
			none
		Return value:
			none
		Behavior:
			Executes events in time stamp order.  Continues executing until no future events remain to execute.
			Simultaneous events are executed in the order they are scheduled.
*/

void RunSimulation(Time endTime);
/*
	RunSimulation
		Parameters:
			none
		Return value:
			none
		Behavior:
			Executes events in time stamp order.  Continues executing until either the current simulation time exceeds
			endTime or no future events remain to execute.  Simultaneous events are executed in the order they are scheduled.
*/

class SimObj
{
	friend Time GetCurrentSimTime();
	friend void RunSimulation();
	friend void RunSimulation(Time endTime);
protected:
	SimObj();
	/*
		SimObj
			Parameters:
				none
			Return value:
				none
			Behavior:
				Constructor, no change in state
	*/

	void ScheduleEventIn(Time deltaTime, Event *ev);
	/*
		ScheduleEventIn
			Parameters:
				Time	time	simulation time delay before event is executed
				Event*	ev		event to be executed
			Return value:
				none
			Behavior:
				Schedules event ev to be executed when the current simulation time reaches the
				current simulation time + deltaTime.
	*/

	void ScheduleEventAt(Time time, Event *ev);
	/*
		ScheduleEventIn
			Parameters:
				Time	time	simulation time delay before event is executed
				Event*	ev		event to be executed
			Return value:
				none
			Behavior:
				Schedules event ev to be executed when the current simulation time reaches time.
	*/

private:
	static Time _currentTime;
	class EventList;
	static EventList _eventList;
};
