OUT_FILE=bfs_main.out
nvcc -std=c++11 src/main.cpp src/gpu/quadratic/bfs_quadratic.cu src/gpu/simple/bfs_simple.cu src/graph/graph.cpp src/cpu/bfs.cpp -o $OUT_FILE \
&& echo "Compiled the program and created executable named $OUT_FILE."

