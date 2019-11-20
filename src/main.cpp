#include <iostream>
#include <chrono>

#include "graph/graph.h"
#include "cpu/bfs.h"
#include "gpu/simple/bfs.cuh"

using namespace std;


// Tests speed of a BFS algorithm
int main() {
	Graph G(AdjacencyList, Directed);
	int startVertex;
	vector<int> distance;
	vector<bool> visited;

	startVertex = 1;

	// CPU
	distance = vector<int>(G.numVertices);
	visited = vector<bool>(G.numVertices);
	auto startTime = chrono::steady_clock::now();
	bfsCPU(startVertex, G, distance, visited);
	auto endTime = std::chrono::steady_clock::now();
	long duration = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
	printf("Elapsed time for CPU implementation : %li ms.\n", duration);

	// Simple GPU
	distance = vector<int>(G.numVertices);
	visited = vector<bool>(G.numVertices);
	startTime = chrono::steady_clock::now();
	bfsGPU(startVertex, G, distance, visited);
	endTime = std::chrono::steady_clock::now();
	duration = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
	printf("Elapsed time for naive linear GPU implementation : %li ms.\n", duration);

	return 0;
}
