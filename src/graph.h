#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <cstdio>
#include <cstdlib>

class Graph {
public:
	Graph(int numVertices, std::vector<std::pair<int, int>> edges);  // creates a graph from given edges
    std::vector<int> adjacencyList; // neighbours of consecutive vertexes
    std::vector<int> edgesOffset; // offset to adjacencyList for every vertex
    std::vector<int> edgesSize; // number of edges for every vertex
    int numVertices;
    int numEdges;
};

#endif // GRAPH_H
