#include <iostream>
#include <chrono>

#include "graph/graph.h"
#include "cpu/bfs.h"
#include "gpu/simple/bfs_simple.cuh"

using namespace std;


void print(vector<int> &v);


class Checker {
	vector<int> expected_answer;
public:
	Checker(vector<int> exp_ans): expected_answer(exp_ans) {}
	void check(vector<int> answer) {
		assert(answer.size() == expected_answer.size());
		bool is_ok = true;
		int position_wrong = -1;
		for (int i = 0; i < answer.size(); ++i) {
			if (answer.at(i) != expected_answer.at(i)) {
				is_ok = false;
				position_wrong = i;
			}
		}
		if (is_ok) {
			printf("CHECKED SUCCESSFULY!\n");
		}
		else {
			printf("Something went wrong!\n");
			printf("Answer at %i equals %i but should be equal to %i", position_wrong, answer[position_wrong], expected_answer[position_wrong]);
		}
	}
};


// Tests speed of a BFS algorithm
int main() {  // TODO: Add arguments to main program (type of graph, file path)
	Graph G(Edges, Undirected);
	int startVertex;
	vector<int> distance;
	vector<bool> visited;

	G.print();

	startVertex = 1;

	// CPU
	distance = vector<int>(G.numVertices);
	visited = vector<bool>(G.numVertices);
	auto startTime = chrono::steady_clock::now();
	bfsCPU(startVertex, G, distance, visited);
	auto endTime = std::chrono::steady_clock::now();
	long duration = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
	printf("Elapsed time for CPU implementation : %li ms.\n", duration);

	Checker checker(distance);

	// Simple GPU
	distance = vector<int>(G.numVertices);
	visited = vector<bool>(G.numVertices);
	startTime = chrono::steady_clock::now();
	bfsGPU(startVertex, G, distance, visited);
	endTime = std::chrono::steady_clock::now();
	duration = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
	printf("Elapsed time for naive linear GPU implementation : %li ms.\n", duration);

	checker.check(distance);

	return 0;
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
