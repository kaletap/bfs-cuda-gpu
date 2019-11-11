#include <gtest/gtest.h>
#include <vector>
#include <set>
#include <unordered_set>
#include <iostream>

#include "../src/graph.h"

#define DEBUG(x)


using namespace std;


void print(vector<set<int>> v) {
	cout << "{ ";
	for (auto const &s : v) {
		cout << "{";
		for (auto elem : s) {
			cout << elem << ", ";
		}
		cout << "}, ";
	}
	cout << "}";
}

void print(vector<int> &v) {
	cout << "{ ";
	for (int i = 0; i < v.size(); ++i) {
		cout << v[i];
		if (i < v.size() - 1)
			cout << ", ";
	}
	cout << " }" << endl;
}


void print(set<int> v) {
	cout << "{ ";
	for (auto elem : v) {
		cout << elem << ", ";
	}
	cout << " }" << endl;
}


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


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
