serial_ocean = serial_ocean
omp_ocean = omp_ocean
cuda_ocean = gpu_ocean

CXX=g++

CXXFLAGS= -O3 -std=c++11 -fno-tree-vectorize -fno-unroll-loops -ffast-math

LDFLAGS = 
CUDACC = nvcc
CUFLAGS = -O3 -arch=sm_35

all: cpu gpu omp

cpu: serial_ocean.cpp ocean_main.o
	$(CXX) $(CXXFLAGS) ocean_main.o serial_ocean.cpp -o $(serial_ocean) $(LDFLAGS)

omp: omp_ocean.cpp ocean_main.o
	$(CXX) $(CXXFLAGS) -fopenmp ocean_main.o omp_ocean.cpp -o $(omp_ocean) $(LDFLAGS)

gpu: ocean_main.o cuda_ocean.cu cuda_ocean_kernels.cu
	$(CUDACC) $(CUFLAGS) ocean_main.o cuda_ocean.cu -o $(cuda_ocean) $(LDFLAGS)

ocean_main.o: ocean_main.cpp
	$(CXX) $(CXXFLAGS) ocean_main.cpp -c -o ocean_main.o

clean:
	rm -f $(serial_ocean)
	rm -f $(omp_ocean)
	rm -f $(cuda_ocean)
	rm -f ocean_main.o
