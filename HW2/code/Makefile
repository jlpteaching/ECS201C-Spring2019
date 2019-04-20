GCC = g++

all: test 

test: test.cc queues.h
	${GCC} -O3 -std=c++11 -pthread test.cc -o test

clean:
	rm test 
