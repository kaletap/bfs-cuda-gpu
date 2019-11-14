#include <ctime>

#include "graph.h"


using namespace std;


Graph::Graph() {
	return;
}


Graph::Graph(int numVertices, vector<pair<int, int>> edges) {
	int numEdges = edges.size();

	vector<vector<int>> adjacencyList(numVertices);

	// Creation of standard adjacency list
	for (auto const &edge : edges) {
		adjacencyList.at(edge.first).push_back(edge.second);
		adjacencyList.at(edge.second).push_back(edge.first);
	}

	// Creation of single vector adjacency list
	for (int i = 0; i < numVertices; ++i) {
		this->edgesOffset.push_back(this->adjacencyList.size());
		this->edgesSize.push_back(adjacencyList[i].size());
		for (int v : adjacencyList[i]) {
			this->adjacencyList.push_back(v);
		}
	}

	this->numVertices = numVertices;
	this->numEdges = numEdges;
}

