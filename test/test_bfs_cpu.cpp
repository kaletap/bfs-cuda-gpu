#include <gtest/gtest.h>
#include <vector>

#include "../src/bfs_cpu.h"
#include "util.h"

#define DEBUG(x)

using namespace std;


TEST(BFS_CPUTest, BFSTest) {
	Graph G(5, {{0,1}, {0, 2}, {1, 2}, {2, 3}, {3, 4}});
	vector<int> distance(G.numVertices);
	vector<bool> visited(G.numVertices);
	int start = 0;
	vector<int> expectedDistance( {0, 1, 1, 2, 3} );
	vector<bool> expectedVisited(G.numVertices, true);

	bfsCPU(start, G, distance, visited);
	DEBUG(print(distance));
	ASSERT_EQ(expectedDistance, distance);
	ASSERT_EQ(expectedVisited, visited);
}
