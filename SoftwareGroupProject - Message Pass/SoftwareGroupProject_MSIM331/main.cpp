#include <iostream>
#include "Node.h"

int main()
{
	srand(1);
	ofstream outFile("Statistics.txt");
	outFile << "Message Passes Wait Times" << endl;

	int numVertices = 10;
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
	adjMatrix[0][3] = 1;
	adjMatrix[1][0] = 1;
	adjMatrix[1][2] = 1;
	adjMatrix[1][3] = 1;
	adjMatrix[1][4] = 1;
	adjMatrix[2][1] = 1;
	adjMatrix[2][5] = 1;
	adjMatrix[3][0] = 1;
	adjMatrix[3][1] = 1;
	adjMatrix[3][9] = 1;
	adjMatrix[4][1] = 1;
	adjMatrix[4][5] = 1;
	adjMatrix[4][7] = 1;
	adjMatrix[5][2] = 1;
	adjMatrix[5][4] = 1;
	adjMatrix[5][6] = 1;
	adjMatrix[6][5] = 1;
	adjMatrix[6][7] = 1;
	adjMatrix[7][6] = 1;
	adjMatrix[7][4] = 1;
	adjMatrix[7][8] = 1;
	adjMatrix[8][7] = 1;
	adjMatrix[8][9] = 1;
	adjMatrix[9][3] = 1;
	adjMatrix[9][8] = 1;

	//=== Vertex 0 === Node 1
	Node *vertex0 = new Node(0, new Triangular(0.9, 1.0, 1.1), new Constant(3.0), adjMatrix, 10, 2, outFile);

	//===Vertex 1=== Node 2
	Node *vertex1 = new Node(1, new Triangular(0.7, 0.8, 0.9), new Constant(3.0), adjMatrix, 10, 4, outFile);

	//===Vertex 2=== Node 3
	Node *vertex2 = new Node(2, new Triangular(0.9, 1.0, 1.1), new Constant(3.0), adjMatrix, 10, 2, outFile);

	//===Vertex 3=== Node 4
	Node *vertex3 = new Node(3, new Triangular(0.8, 0.9, 1.0), new Constant(3.0), adjMatrix, 10, 3, outFile);

	//===Vertex 4=== Node 5
	Node *vertex4 = new Node(4, new Triangular(0.8, 0.9, 1.0), new Constant(3.0), adjMatrix, 10, 3, outFile);

	//===Vertex 5=== Node 6
	Node *vertex5 = new Node(5, new Triangular(0.8, 0.9, 1.0), new Constant(3.0), adjMatrix, 10, 3, outFile);

	//===Vertex 6=== Node 7
	Node *vertex6 = new Node(6, new Triangular(0.9, 1.0, 1.1), new Constant(3.0), adjMatrix, 10, 2, outFile);

	//===Vertex 7=== Node 8
	Node *vertex7 = new Node(7, new Triangular(0.8, 0.9, 1.0), new Constant(3.0), adjMatrix, 10, 3, outFile);
	
	//===Vertex 8=== Node 9
	Node *vertex8 = new Node(8, new Triangular(0.9, 1.0, 1.1), new Constant(3.0), adjMatrix, 10, 2, outFile);
	
	//===Vertex 9=== Node 10
	Node *vertex9 = new Node(9, new Triangular(0.9, 1.0, 1.1), new Constant(3.0), adjMatrix, 10, 2, outFile);
	
	//Set Neighbors
	vertex0->SetNeighbor(1, vertex1);
	vertex0->SetNeighbor(3, vertex3);

	vertex1->SetNeighbor(0, vertex0);
	vertex1->SetNeighbor(2, vertex2);
	vertex1->SetNeighbor(3, vertex3);
	vertex1->SetNeighbor(4, vertex4);

	vertex2->SetNeighbor(1, vertex1);
	vertex2->SetNeighbor(5, vertex5);

	vertex3->SetNeighbor(0, vertex0);
	vertex3->SetNeighbor(1, vertex1);
	vertex3->SetNeighbor(9, vertex9);

	vertex4->SetNeighbor(1, vertex1);
	vertex4->SetNeighbor(5, vertex5);
	vertex4->SetNeighbor(7, vertex7);

	vertex5->SetNeighbor(2, vertex2);
	vertex5->SetNeighbor(4, vertex4);
	vertex5->SetNeighbor(6, vertex6);

	vertex6->SetNeighbor(5, vertex5);
	vertex6->SetNeighbor(7, vertex7);

	vertex7->SetNeighbor(4, vertex4);
	vertex7->SetNeighbor(6, vertex6);
	vertex7->SetNeighbor(8, vertex8);

	vertex8->SetNeighbor(7, vertex7);
	vertex8->SetNeighbor(9, vertex9);

	vertex9->SetNeighbor(3, vertex3);
	vertex9->SetNeighbor(8, vertex8);

	RunSimulation();
	
	vertex0->OutputStatistics();
	vertex1->OutputStatistics();
	vertex2->OutputStatistics();
	vertex3->OutputStatistics();
	vertex4->OutputStatistics();
	vertex5->OutputStatistics();
	vertex6->OutputStatistics();
	vertex7->OutputStatistics();
	vertex8->OutputStatistics();
	vertex9->OutputStatistics();


	cin.get();
}