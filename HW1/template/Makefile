
CXX= g++
CXXFLAGS= -O3 -std=c++11
LDFLAGS =  

all: serial_ocean omp_ocean

serial_ocean: serial_ocean.cpp ocean_main.cpp
	$(CXX) $(CXXFLAGS) ocean_main.cpp serial_ocean.cpp -o serial_ocean $(LDFLAGS)

omp_ocean: omp_ocean.cpp ocean_main.cpp
	$(CXX) $(CXXFLAGS) -fopenmp ocean_main.cpp omp_ocean.cpp -o omp_ocean $(LDFLAGS)

clean:
	rm -f serial_ocean
	rm -f omp_ocean
