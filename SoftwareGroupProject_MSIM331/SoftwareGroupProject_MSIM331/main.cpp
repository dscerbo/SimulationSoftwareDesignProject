#include <iostream>
#include "Distribution.h"

Distribution *Distributor();

using namespace std;

int main()
{
	Distribution *Distribution;

	int numVertices;
	cout << "Enter # of vertices: ";
	cin >> numVertices;

	//2D array (its an array to pointers to arrays)
	int **adjMatrix = new int*[numVertices];
	for (int i = 0; i < numVertices; ++i)
		adjMatrix[i] = new int[numVertices];

	//initialize list to nothing being connected
	for (int i = 0; i < numVertices; i++)
	{
		for (int j = 0; j < numVertices; j++)
		{
			adjMatrix[i][j] = 0;
		}
	}

	/*
	1. User enters the number of edges for each node
	2. User then specifies which node it will be connected ex: [i][user input] = 1
	*/
	int numEdges;
	int edgeName;
	for (int i = 0; i < numVertices; i++)
	{
		cout << "Enter a type of distrbution for node " << i << ": " << endl;
		Distributor();
		cout << "Enter the node's # of edges";
		cin >> numEdges;
		cout << endl;
		for (int j = 0; j < numEdges; j++)
		{
			cout << "Enter edge to connect ";
			cin >> edgeName;
			cout << endl;
			adjMatrix[i][edgeName] = 1;
		}
	}

	for (int i = 0; i < numVertices; i++)
	{
		for (int j = 0; j < numVertices; j++)
		{
			cout << adjMatrix[i][j];
		}
		cout << endl;
	}
	cout << endl;

	cout << "<enter> to terminate: ";
	cin.get();
	cin.get();
}

Distribution *Distributor()
{
	cout << "1. Exponential(mean)" << endl
		<< "2. Uniform(min, max)" << endl
		<< "3. Triangular(min, expected, max)" << endl
		<< "4. Normal(mean, stdev)" << endl
		<< "5. Poisson(mean)" << endl
		<< "6. Constant(mean)" << endl
		<< "7. Weibull(scale, shape)" << endl
		<< "8. Erlang(scale, shape)" << endl;

	double a = 0;
	cout << "Enter the mean of the exponential distribution: ";
	cin >> a;
	Distribution *distribution = new Exponential(a);
	return distribution;
}
