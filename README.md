# Parallel BFS with CUDA

This projects aims to implement Breadth First Search Algorithm on CUDA which would outperform simple sequential implementation.

Nvidia paper: https://research.nvidia.com/publication/scalable-gpu-graph-traversal (Merrill, Garland, Grimshaw)

## Goals:
1.1 Create Graph class 
1.2 Test Graph class 
2.1 Implement sequential BFS
2.2 Test sequential BFS
3.1 Implement (simple) parallel BFS with CUDA
3.2 Test (simple) parallel BFS
4.1 Implement Merill parallel BFS with CUDA
4.2 Test Merill parallel BFS
5.1 Performance comparison and conclusions

## Parallelization strategy

Simple, sequential Breadth First Search has O(|V| + |E|) complexity - we visit every vertex exactly once and every edge at most once. Therefore, it would be desirable for our parallel algorithm to have the same asymptotic complexity. 

At first, we will consider simple parallelization strategy that has the above complexity. In each BFS level it simply traverses all vertexes in the queue in parallel and creates a new queue.

Then, we will try to imlement more sophisticated algorithm. 
As described in Merill et. al our strategy is following:

* expand adjacent neighbors in parallel
* implement out-of-vore edge and vertex frontiers
* use local prefix sum in place of local atomic operations for determining enqueue offsets
* use a best-effort bitmask for efficient neighbor filtering

## Requirements: 

* gtest (https://github.com/google/googletest) for testing

## Credits

Thanks to:

* D. Merill, M. Garland, A. Grimshaw and their paper "Scalable GPU Graph Traversal" which helped me understand this algorithm
* Github user rafalk342 (https://github.com/rafalk342/bfs-cuda) whose repo helped me get started with implementation of my first code running on GPU with cuda.
