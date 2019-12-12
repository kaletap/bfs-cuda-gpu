#include "bfs_quadratic.cuh"

using namespace std;

#define DEBUG(x)
#define N_THREADS_PER_BLOCK (1 << 2)



__global__
void compute_next_layer_distance(int n, int *adjacencyList, int *edgesOffset, int *edgesSize, int *distance, int level, bool *done) {
	const int tid = blockIdx.x * blockDim.x + threadIdx.x;
	if (tid < n) {
		if (distance[tid] == level) {
			for (int i = edgesOffset[tid]; i < edgesOffset[tid] + edgesSize[tid]; ++i) {
				int v = adjacencyList[i];
				if (distance[v] == INT_MAX) {
					*done = false;
					distance[v] = level + 1;
				}
			}
		}
	}
}


// Assumes that distance is a vector of all INT_MAX (except at start position)
void bfsGPUQuadratic(int start, Graph &G, vector<int> &distance, vector<bool> &visited) {

	const int n_blocks = (G.numVertices + N_THREADS_PER_BLOCK - 1) / N_THREADS_PER_BLOCK;

	// Initialization of GPU variables
	int *d_adjacencyList;
	int *d_edgesOffset;
	int *d_edgesSize;
	int *d_distance; // output
	bool done = false;
	const bool true_value = true;

	// Initialization of CPU variables
	bool *d_done;
	int level = 0;

	// Allocation on device
	const int size = G.numVertices * sizeof(int);
	const int adjacencySize = G.adjacencyList.size() * sizeof(int);
	cudaMalloc((void **)&d_adjacencyList, adjacencySize);
	cudaMalloc((void **)&d_edgesOffset, size);
	cudaMalloc((void **)&d_edgesSize, size);
	cudaMalloc((void **)&d_distance, size);
	cudaMalloc((void **)&d_done, sizeof(bool));  // malloc of single value is also important


	// Copy inputs to device
	cudaMemcpy(d_adjacencyList, &G.adjacencyList[0], adjacencySize, cudaMemcpyHostToDevice);
	cudaMemcpy(d_edgesOffset, &G.edgesOffset[0], size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_edgesSize, &G.edgesSize[0], size, cudaMemcpyHostToDevice);
	distance[start] = 0;
	cudaMemcpy(d_distance, distance.data(), size, cudaMemcpyHostToDevice);

	while (!done) {
		cudaMemcpy(d_done, &true_value, sizeof(bool), cudaMemcpyHostToDevice);
		compute_next_layer_distance <<<n_blocks, N_THREADS_PER_BLOCK>>> (G.numVertices, d_adjacencyList, d_edgesOffset, d_edgesSize, d_distance, level, d_done);
		cudaDeviceSynchronize();
		cudaMemcpy(&done, d_done, sizeof(bool), cudaMemcpyDeviceToHost);
		++level;
		if (level > G.numVertices) {
			cerr << "Number of iterations exceeded number of vertices!" << endl;
			break;
		}
	}

	// Copying output back to host
	cudaMemcpy(&distance[0], d_distance, size, cudaMemcpyDeviceToHost);

	// Cleanup
	cudaFree(d_adjacencyList);
	cudaFree(d_edgesOffset);
	cudaFree(d_edgesSize);
	cudaFree(d_distance);
}
