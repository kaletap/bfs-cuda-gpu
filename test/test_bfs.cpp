#include <gtest/gtest.h>
#include <vector>

#include "../src/bfs_cpu.h"
#include "../src/bfs_gpu.cuh"
#include "util.h"

#define DEBUG(x)

using namespace std;


class BFSTest : public ::testing::Test {
protected:
	void SetUp() override {
		graph = Graph(5, {{0,1}, {0, 2}, {1, 2}, {2, 3}, {3, 4}});
		distance = vector<int>(graph.numVertices);
		visited = vector<bool>(graph.numVertices);
		expectedVisited = vector<bool>(graph.numVertices, true);
	}
	Graph graph;
	vector<int> distance;
	vector<bool> visited;
	int start;
	vector<int> expectedDistance;
	vector<bool> expectedVisited;
};


TEST_F(BFSTest, BFS_CPU_Test_start0) {
	start = 0;
	expectedDistance = vector<int>( {0, 1, 1, 2, 3} );
	bfsCPU(start, graph, distance, visited);
	EXPECT_EQ(expectedDistance, distance);
	EXPECT_EQ(expectedVisited, visited);
}


TEST_F(BFSTest, BFS_CPU_Test_start1) {
	start = 1;
	expectedDistance = vector<int>( {1, 0, 1, 2, 3} );
	bfsCPU(start, graph, distance, visited);
	EXPECT_EQ(expectedDistance, distance);
	EXPECT_EQ(expectedVisited, visited);
}


TEST_F(BFSTest, BFS_CPU_Test_start2) {
	start = 2;
	expectedDistance = vector<int>( {1, 1, 0, 1, 2} );
	bfsCPU(start, graph, distance, visited);
	EXPECT_EQ(expectedDistance, distance);
	EXPECT_EQ(expectedVisited, visited);
}


TEST_F(BFSTest, BFS_Simple_GPU_Test_start0) {
	start = 0;
	expectedDistance = vector<int>( {0, 1, 1, 2, 3} );
	bfsGPU(start, graph, distance, visited);
	DEBUG(print(distance));
	EXPECT_EQ(expectedDistance, distance);
//	EXPECT_EQ(expectedVisited, visited);
}


TEST_F(BFSTest, BFS_Simple_GPU_Test_start1) {
	start = 1;
	expectedDistance = vector<int>( {1, 0, 1, 2, 3} );
	bfsGPU(start, graph, distance, visited);
	DEBUG(print(distance));
	EXPECT_EQ(expectedDistance, distance);
//	EXPECT_EQ(expectedVisited, visited);
}
