#include <gtest/gtest.h>
#include <vector>
#include <set>
#include <unordered_set>
#include <iostream>

#include "../src/graph/graph.h"
#include "util.h"

#define DEBUG(x)


using namespace std;


TEST(GraphTest, GraphCreation) {
	Graph G(5, {{0,1}, {0, 2}, {1, 2}, {3, 4}});
	vector<set<int>> expectedAdjacencyList ({ {1, 2}, {0, 2}, {0, 1}, {4}, {3} });

	DEBUG(print(G.adjacencyList));
	DEBUG(print(G.edgesOffset));

	for (int v = 0; v < G.numVertices; ++v) {
		set<int> neighbors;
		for (int i = G.edgesOffset[v]; i < G.edgesOffset[v] + G.edgesSize[v]; ++i)
			neighbors.insert(G.adjacencyList[i]);
		DEBUG(print(neighbors));
		ASSERT_EQ(neighbors, expectedAdjacencyList[v]);
	}
}
