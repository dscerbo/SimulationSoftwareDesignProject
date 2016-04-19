#include <iostream>
#include "Node.h"

int main()
{
	int numVertices = 2;
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

	//===Vertex 0===
	Node *vertex0 = new Node(0, new Constant(2.0), new Constant(10.0), adjMatrix, 2, 1);

	//1 edge
	adjMatrix[0][1] = 1;

	//===Vertex 1===
	Node *vertex1 = new Node(1, new Constant(2.0), new Constant(10.0), adjMatrix, 2, 1);

	//1 edge
	adjMatrix[1][0] = 1;

	RunSimulation();
	
	cin.get();
}