#include <iostream>
#include "Node.h"

int main()
{
	int numVertices = 4;
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
	Node *vertex0 = new Node(0, new Constant(2.0), new Constant(10.0), adjMatrix, 4, 2);

	//2 edges
	adjMatrix[0][1] = 1;
	adjMatrix[0][3] = 1;

	//===Vertex 1===
	Node *vertex1 = new Node(0, new Constant(2.0), new Constant(10.0), adjMatrix, 4, 2);

	//2 edges
	adjMatrix[1][0] = 1;
	adjMatrix[0][2] = 1;

	//===Vertex 2===
	Node *vertex2 = new Node(0, new Constant(2.0), new Constant(10.0), adjMatrix, 4, 2);

	//2 edges
	adjMatrix[2][1] = 1;
	adjMatrix[2][3] = 1;

	//===Vertex 3===
	Node *vertex3 = new Node(0, new Constant(2.0), new Constant(10.0), adjMatrix, 4, 2);

	//2 edges
	adjMatrix[3][0] = 1;
	adjMatrix[3][2] = 1;

	RunSimulation();
	
	cin.get();
}