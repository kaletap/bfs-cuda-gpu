#include "graph.h"


using namespace std;


void print_vector(string title, vector<int> &v);


Graph::Graph(Format format, Direction direction) {
	switch (format) {
		case Empty:
			return;
			break;
		case Edges: {
			int numVertices, numEdges;
			cout << "Started reading graph" << endl;
			cin >> numVertices >> numEdges;
			vector<vector<int>> adjacencyList(numVertices);
			int v, w;
			for (int i = 0; i < numEdges; ++i) {
				cin >> v >> w;
				adjacencyList[v].push_back(w);
				if (direction == Undirected) {
					adjacencyList[w].push_back(v);
				}
			}
			this->init(adjacencyList, numEdges);
			cout << "Finished reading graph" << endl;
			break;
		}
		case AdjacencyList: {
			int numVertices, numEdges;
			cout << "Started reading graph" << endl;
			cin >> numVertices >> numEdges;
			vector<vector<int>> adjacencyList(numVertices);
			string line;
			for (int v = 0; v < numVertices; ++v) {
				getline(cin, line);
				stringstream splitter(line);
				int w;
				while (splitter >> w) {
					adjacencyList[v].push_back(w);
					if (direction == Undirected) {
						cerr << "Warning: You are reading graph using adjacency list as undirected";
						adjacencyList[w].push_back(v);
					}
				}
			}
			this->init(adjacencyList, numEdges);
			cout << "Finished reading graph" << endl;
			break;
		}
	}


}


Graph::Graph(int numVertices, vector<pair<int, int>> edges) {
	int numEdges = edges.size();

	vector<vector<int>> adjacencyList(numVertices);

	// Creation of standard adjacency list
	for (auto const &edge : edges) {
		adjacencyList.at(edge.first).push_back(edge.second);
		adjacencyList.at(edge.second).push_back(edge.first);
	}

	this->init(adjacencyList, numEdges);
}



Graph::Graph(vector<vector<int>> adjacencyList) {
	int numEdges = 0;
	for (auto const &neighbors : adjacencyList) {
		for (int v : neighbors) {
			++numEdges;
		}
	}
	this->init(adjacencyList, numEdges);
}


void Graph::init(vector<vector<int>> adjacencyList, int numEdges) {
	const int numVertices = adjacencyList.size();
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


void Graph::print() {
	printf("Graph(numVertices = %i, numEdges = %i)\n", numVertices, numEdges);
	print_vector("AdjacencyList:", adjacencyList);
	print_vector("edgesOffset:", edgesOffset);
	print_vector("edgesSize:", edgesSize);
}


void print_vector(string title, vector<int> &v) {
	cout << title << " { ";
	for (int i = 0; i < v.size(); ++i) {
		cout << v[i];
		if (i < v.size() - 1)
			cout << ", ";
	}
	cout << " }" << endl;
}
