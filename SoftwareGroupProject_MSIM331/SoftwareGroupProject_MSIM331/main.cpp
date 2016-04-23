#include <iostream>
#include "Node.h"

int main()
{
	int numVertices = 3;
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
	///Make adjMatrix static variable inside Node class
	adjMatrix[0][1] = 1;
	adjMatrix[1][0] = 1;
	adjMatrix[1][2] = 1;
	adjMatrix[2][1] = 1;

	//===Vertex 0===
	Node *vertex0 = new Node(0, new Constant(2.0), new Constant(10.0), adjMatrix, 3, 1);

	//1 edge
	

	//===Vertex 1===
	Node *vertex1 = new Node(1, new Constant(2.0), new Constant(10.0), adjMatrix, 3, 2);

	//1 edge
	

	//===Vertex 2===
	Node *vertex2 = new Node(2, new Constant(2.0), new Constant(10.0), adjMatrix, 3, 1);

	vertex0->SetNeighbor(1, vertex1);
	vertex1->SetNeighbor(0, vertex0);
	vertex1->SetNeighbor(2, vertex2);
	vertex2->SetNeighbor(1, vertex1);
	
	RunSimulation();
	
	cin.get();
}