#include "bfs.h"

using namespace std;


void bfsCPU(int start, Graph &G, std::vector<int> &distance, std::vector<bool> &visited) {
	fill(distance.begin(), distance.end(), INT_MAX);
	distance[start] = 0;
	visited[start] = true;
	queue<int> to_visit;
	to_visit.push(start);

	while (!to_visit.empty()) {
		int current = to_visit.front();
		to_visit.pop();
		for (int i = G.edgesOffset[current]; i < G.edgesOffset[current] + G.edgesSize[current]; ++i) {
			int v = G.adjacencyList[i];
			if (!visited[v]) {
				distance[v] = distance[current] + 1;
				visited[v] = true;
				to_visit.push(v);
			}
		}
	}
}
