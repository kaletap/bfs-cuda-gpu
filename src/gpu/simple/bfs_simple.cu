#include "bfs_simple.cuh"

using namespace std;

#define DEBUG(x)
#define N_THREADS_PER_BLOCK (1 << 5)



__global__
void initializeDeviceArray(int n, int *d_arr, int value, int start_index) {
	const int tid = blockIdx.x * blockDim.x + threadIdx.x;
	if (tid == start_index) {
		d_arr[start_index] = 0;
	}
	else if (tid < n) {
		d_arr[tid] = value;
	}
}


__global__
void printDeviceArray(int *d_arr, int n) {
	const int tid = blockIdx.x * blockDim.x + threadIdx.x;
	if (tid < n) {
		printf("d_arr[%i] = %i \n", tid, d_arr[tid]);
	}
}


/*
 * Given a graph and a current queue computes next vertices (vertex frontiers) to traverse.
 */
__global__
void computeNextQueue(int *adjacencyList, int *edgesOffset, int *edgesSize, int *distance,
		int queueSize, int *currentQueue, int *nextQueueSize, int *nextQueue, int level) {
	const int tid = blockIdx.x * blockDim.x + threadIdx.x;  // thread id
	if (tid < queueSize) {  // visit all vertexes in a queue in parallel
		int current = currentQueue[tid];
		for (int i = edgesOffset[current]; i < edgesOffset[current] + edgesSize[current]; ++i) {
			int v = adjacencyList[i];
			if (distance[v] == INT_MAX) {
				distance[v] = level + 1;
				int position = atomicAdd(nextQueueSize, 1);
				nextQueue[position] = v;
			}
		}
	}
}


void bfsGPU(int start, Graph &G, vector<int> &distance, vector<bool> &visited) {

	const int n_blocks = (G.numVertices + N_THREADS_PER_BLOCK - 1) / N_THREADS_PER_BLOCK;

	// Initialization of GPU variables
	int *d_adjacencyList;
	int *d_edgesOffset;
	int *d_edgesSize;
	int *d_firstQueue;
	int *d_secondQueue;
	int *d_nextQueueSize;
	int *d_distance; // output

	// Initialization of CPU variables
	int currentQueueSize = 1;
	const int NEXT_QUEUE_SIZE = 0;
	int level = 0;

	// Allocation on device
	const int size = G.numVertices * sizeof(int);
	const int adjacencySize = G.adjacencyList.size() * sizeof(int);
	cudaMalloc((void **)&d_adjacencyList, adjacencySize);
	cudaMalloc((void **)&d_edgesOffset, size);
	cudaMalloc((void **)&d_edgesSize, size);
	cudaMalloc((void **)&d_firstQueue, size);
	cudaMalloc((void **)&d_secondQueue, size);
	cudaMalloc((void **)&d_distance, size);
	cudaMalloc((void **)&d_nextQueueSize, sizeof(int));

	// Copy inputs to device
	cudaMemcpy(d_adjacencyList, &G.adjacencyList[0], adjacencySize, cudaMemcpyHostToDevice);
	cudaMemcpy(d_edgesOffset, &G.edgesOffset[0], size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_edgesSize, &G.edgesSize[0], size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_nextQueueSize, &NEXT_QUEUE_SIZE, sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(d_firstQueue, &start, sizeof(int), cudaMemcpyHostToDevice);
//	initializeDeviceArray<<<n_blocks, N_THREADS_PER_BLOCK>>> (G.numVertices, d_distance, INT_MAX, start); // FOR SOME REASON USING THIS KERNEL DOESNT WORK
//	cudaDeviceSynchronize();
	distance = vector<int> (G.numVertices, INT_MAX);
	distance[start] = 0;
	auto startTime = chrono::steady_clock::now();
	cudaMemcpy(d_distance, distance.data(), size, cudaMemcpyHostToDevice);

	while (currentQueueSize > 0) {
		int *d_currentQueue;
		int *d_nextQueue;
		if (level % 2 == 0) {
			d_currentQueue = d_firstQueue;
			d_nextQueue = d_secondQueue;
		}
		else {
			d_currentQueue = d_secondQueue;
			d_nextQueue = d_firstQueue;
		}
		computeNextQueue<<<n_blocks, N_THREADS_PER_BLOCK>>> (d_adjacencyList, d_edgesOffset, d_edgesSize, d_distance,
				currentQueueSize, d_currentQueue, d_nextQueueSize, d_nextQueue, level);
		cudaDeviceSynchronize();
		++level;
		cudaMemcpy(&currentQueueSize, d_nextQueueSize, sizeof(int), cudaMemcpyDeviceToHost);
		cudaMemcpy(d_nextQueueSize, &NEXT_QUEUE_SIZE, sizeof(int), cudaMemcpyHostToDevice);
	}

	cudaMemcpy(&distance[0], d_distance, size, cudaMemcpyDeviceToHost);
	auto endTime = std::chrono::steady_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
	printf("Elapsed time for naive linear GPU implementation (without copying graph) : %li ms.\n", duration);

	// Cleanup
	cudaFree(d_adjacencyList);
	cudaFree(d_edgesOffset);
	cudaFree(d_edgesSize);
	cudaFree(d_firstQueue);
	cudaFree(d_secondQueue);
	cudaFree(d_distance);
}
