#include <gtest/gtest.h>
#include <vector>

#include "../src/bfs_cpu.h"
#include "../src/bfs_gpu.h"
#include "util.h"

#define DEBUG(x)

using namespace std;


class BFSTest : public ::testing::Test {
protected:
	void SetUp() override {
		graph = Graph(5, {{0,1}, {0, 2}, {1, 2}, {2, 3}, {3, 4}});
		distance = vector<int>(graph.numVertices);
		visited = vector<bool>(graph.numVertices);
		start = 0;
		expectedDistance = vector<int>( {0, 1, 1, 2, 3} );
		expectedVisited = vector<bool>(graph.numVertices, true);
	}
	Graph graph;
	vector<int> distance;
	vector<bool> visited;
	int start;
	vector<int> expectedDistance;
	vector<bool> expectedVisited;
};


TEST_F(BFSTest, BFS_CPU_Test) {
	bfsCPU(start, graph, distance, visited);
	DEBUG(print(distance));
	EXPECT_EQ(expectedDistance, distance);
	EXPECT_EQ(expectedVisited, visited);
}


TEST_F(BFSTest, BFS_Simple_GPU_Test) {
	bfsGPU(start, graph, distance, visited);
	DEBUG(print(distance));
	EXPECT_EQ(expectedDistance, distance);
	EXPECT_EQ(expectedVisited, visited);
}
