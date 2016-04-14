#include <iostream>
#include "Simulation.h"
#include "Node.h"
#include "Distribution.h"
#include "Message.h"
#include "FIFO.h"

using namespace std;

void main()
{
	

	RunSimulation();

	cout << "<enter> to terminate: ";
	cin.get();
}
