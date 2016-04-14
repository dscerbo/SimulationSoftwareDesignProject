#include <iostream>

int main() {
	int numVertices;
	std::cout << "# of vertices";
	std::cin >> numVertices; 
	
	//2D array (its an array to pointers to arrays)
	int **adjMatrix = new int*[numVertices];
	for (int i = 0; i < numVertices; ++i)
		adjMatrix[i] = new int[numVertices];
}