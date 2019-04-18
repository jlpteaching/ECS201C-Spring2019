// Compile this with:
// g++ -O3 -std=c++0x -pthread test.cc -o test

#include <sys/time.h>
#include "queues.h"
#include <iostream>
#include <thread>

#define TEST_RW
#define TEST_SPSC
#define TEST_SPMC
#define TEST_MPSC
const int kNumOperations = 10000000;
const int kMaxQueueSize = 1000;

struct Data {
  Data(int x, int y) : a(x), b(y) { }
  Data() : a(-1), b(-1) { }
  int a;
  int b;
};

void producer_func(FixedSizeQueueInterface<Data>* queue, int total_pushes) {
  int num_pushes = 0;
  while (num_pushes < total_pushes) {
    if (queue->Write(Data(12, 13))) {
      num_pushes++;
    }
  }
}

void consumer_func(FixedSizeQueueInterface<Data>* queue, int total_pulls) {
  int num_pulls = 0;
  while (num_pulls < total_pulls) {
    Data data;
    if (queue->Read(&data)) {
      num_pulls++;
    }
  }
}

int main(int argc, char *argv[]) {

  if (argc != 4) {
      std::cout << "Error! Usage: test <num_iterations> <producer_threads>"
         " <consumer_threads>\n";
      std::cout << "<producer_threads> used only for MPSC queue, and "
         "<consumer_threads> used only for SPMC queue\n";
      return 1;
  }
    
  int num_iterations = atoi(argv[1]);
  int num_prod_threads = atoi(argv[2]);
  int num_cons_threads = atoi(argv[3]);

  struct timeval start;
  struct timeval end;
  double elapsed_seconds = 0;
  double avg_tput = 0;
  int i = 0;
  int j = 0;
  
  std::thread producer_thread[num_prod_threads];
  std::thread consumer_thread[num_cons_threads];

#ifdef TEST_RW
  std::cout << "Testing reader-writer Mutex Queue\n";
  std::cout << "Number of iterations:" << num_iterations << std::endl;
  std::cout << "Producers:" << num_prod_threads << 
      " Consumers:" << num_cons_threads << std::endl;
  while (i++ < num_iterations){
      MutexFixedSizeQueue<Data> mutex_queue(kMaxQueueSize);
      gettimeofday(&start, NULL);
      for (j = 0; j < num_prod_threads; j++) {
          producer_thread[j] = std::thread(producer_func, &mutex_queue, 
                  kNumOperations/num_prod_threads);
      }
      for (j = 0; j < num_cons_threads; j++) {
          consumer_thread[j] = std::thread(consumer_func, &mutex_queue, 
                  kNumOperations/num_cons_threads);
      }
      for (j = 0; j < num_prod_threads; j++) {
          producer_thread[j].join();
      }
      for (j = 0; j < num_cons_threads; j++) {
          consumer_thread[j].join();
      }
      gettimeofday(&end, NULL);
      elapsed_seconds = end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec)/1e6;
      avg_tput += kNumOperations/elapsed_seconds;
      if(!mutex_queue.isEmpty()) {
          std::cout << "Error! Queue should be empty!" << std::endl;
          exit(0);
      }
  }
  std::cout << "Mutex Queue throughput: " << avg_tput/num_iterations << " ops/sec\n";
#endif

#ifdef TEST_SPSC
  std::cout << "\nTesting LockFree Queue (SPSC)\n";
  std::cout << "Number of iterations:" << num_iterations << std::endl;
  std::cout << "Producers:1 Consumers:1" << std::endl;
  avg_tput = 0;
  i = 0;
  while (i++ < num_iterations){
      SingleProducerSingleConsumerFixedSizeQueue<Data> lockfree_queue(kMaxQueueSize);
      gettimeofday(&start, NULL);
      producer_thread[0] = std::thread(producer_func, &lockfree_queue, 
              kNumOperations);
      consumer_thread[0] = std::thread(consumer_func, &lockfree_queue, 
              kNumOperations);
      producer_thread[0].join();
      consumer_thread[0].join();
      gettimeofday(&end, NULL);
      elapsed_seconds = end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec)/1e6;
      avg_tput += kNumOperations/elapsed_seconds;
      if(!lockfree_queue.isEmpty()) {
          std::cout << "Error! Queue should be empty!" << std::endl;
          exit(0);
      }
  }
  std::cout << "Lock Free Queue (SPSC) throughput:  " << avg_tput/num_iterations << " ops/sec\n";
#endif

#ifdef TEST_SPMC
  std::cout << "\nTesting LockFree Queue (SPMC)\n";
  std::cout << "Number of iterations:" << num_iterations << std::endl;
  std::cout << "Producers:1 Consumers:" << num_cons_threads << std::endl;
  avg_tput = 0;
  i = 0;
  while (i++ < num_iterations){
      SingleProducerMultipleConsumerFixedSizeQueue<Data> lockfree_queue(kMaxQueueSize);
      gettimeofday(&start, NULL);
      producer_thread[0] = std::thread(producer_func, &lockfree_queue, 
              kNumOperations);
      for (j = 0; j < num_cons_threads; j++) {
          consumer_thread[j] = std::thread(consumer_func, &lockfree_queue, 
                  kNumOperations/num_cons_threads);
      }
      producer_thread[0].join();
      for (j = 0; j < num_cons_threads; j++) {
          consumer_thread[j].join();
      }
      gettimeofday(&end, NULL);
      elapsed_seconds = end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec)/1e6;
      avg_tput += kNumOperations/elapsed_seconds;
      if(!lockfree_queue.isEmpty()) {
          std::cout << "Error! Queue should be empty!" << std::endl;
          exit(0);
      }
  }
  std::cout << "Lock Free Queue (SPMC) throughput:  " << avg_tput/num_iterations << " ops/sec\n";
#endif

#ifdef TEST_MPSC
  std::cout << "\nTesting LockFree Queue (MPSC)\n";
  std::cout << "Number of iterations:" << num_iterations << std::endl;
  std::cout << "Producers:" << num_prod_threads << " Consumers:1" << std::endl;
  avg_tput = 0;
  i = 0;
  while (i++ < num_iterations){
      MultipleProducerSingleConsumerFixedSizeQueue<Data> lockfree_queue(kMaxQueueSize);
      gettimeofday(&start, NULL);
      
      for (j = 0; j < num_prod_threads; j++) {
          producer_thread[j] = std::thread(producer_func, &lockfree_queue, 
                  kNumOperations/num_prod_threads);
      }
      consumer_thread[0] = std::thread(consumer_func, &lockfree_queue, 
              kNumOperations);

      for (j = 0; j < num_prod_threads; j++) {
          producer_thread[j].join();
      }
      consumer_thread[0].join();
      
      gettimeofday(&end, NULL);
      elapsed_seconds = end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec)/1e6;
      avg_tput += kNumOperations/elapsed_seconds;
      if(!lockfree_queue.isEmpty()) {
          std::cout << "Error! Queue should be empty!" << std::endl;
          exit(0);
      }
  }
  std::cout << "Lock Free Queue (MPSC) throughput:  " << avg_tput/num_iterations << " ops/sec\n";
#endif


  return 0;
}
