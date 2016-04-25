#include <iostream>
#include "Node.h"

int main()
{
	ofstream outFile("Statistics.txt");


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


	//vertex edges
	
	adjMatrix[0][1] = 1;
	adjMatrix[1][0] = 1;
	adjMatrix[1][2] = 1;
	adjMatrix[2][1] = 1;

	//=== Vertex 0 === Node 1
	Node *vertex0 = new Node(0, new Triangular(0.9, 1.0, 1.1), new Constant(.5), adjMatrix, 3, 1, outFile);

	//===Vertex 1=== Node 2
	Node *vertex1 = new Node(1, new Triangular(0.7, 0.8, 0.9), new Constant(.5), adjMatrix, 3, 2, outFile);

	Node *vertex2 = new Node(2, new Triangular(0.7, 0.8, 0.9), new Constant(.5), adjMatrix, 3, 1, outFile);



	vertex0->SetNeighbor(1, vertex1);
	vertex1->SetNeighbor(0, vertex0);
	vertex1->SetNeighbor(2, vertex2);
	vertex2->SetNeighbor(1, vertex1);

	RunSimulation();
	
	vertex0->OutputStatistics();
	vertex1->OutputStatistics();


	cin.get();
}