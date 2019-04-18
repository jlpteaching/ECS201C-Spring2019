#ifndef QUEUES_H_
#define QUEUES_H_

#include <atomic>
#include <deque>
#include <mutex>

// Defines the interface for the Fixed Size Queue
template<typename T>
class FixedSizeQueueInterface {
 public:
  virtual ~FixedSizeQueueInterface() { }
  virtual bool Read(T* data) = 0;
  virtual bool Write(const T& data) = 0;
};

// Implements a fixed-size queue using a Mutex
/* Update this to use reader writer locks */
template<typename T>
class MutexFixedSizeQueue : public FixedSizeQueueInterface<T> {
 public:

  // Simple helper class to ensure a lock is unlocked once the scope is exited
  class ScopedLock {
   public:
    ScopedLock(std::mutex* mutex) : mutex_(mutex) {
      mutex_->lock();
    }
    ~ScopedLock() {
      mutex_->unlock();
    }
   private:
    std::mutex* mutex_;
  };

  MutexFixedSizeQueue(int max_size) : max_size_(max_size) { }

  // Reads the next data item into 'data', returns true
  // if successful or false if the queue was empty.
  bool Read(T* data) {
    ScopedLock lock(&mutex_);
    if (queue_.empty()) {
      return false;
    }
    *data = queue_.front();
    queue_.pop_front();
    return true;
  }

  // Writes 'data' into the queue.  Returns true if successful
  // or false if the queue was full.
  bool Write(const T& data) {
    ScopedLock lock(&mutex_);
    if (queue_.size() > max_size_) {
      return false;
    }
    queue_.push_back(data);
    return true;
  }

  bool isEmpty() {
      return queue_.empty();
  }

 private:
  std::deque<T> queue_;
  int max_size_;
  std::mutex mutex_;
};

// Implements a fixed-size queue using no lock, but limited to a single
// producer thread and a single consumer thread.
template<typename T>
class SingleProducerSingleConsumerFixedSizeQueue : public FixedSizeQueueInterface<T> {
 public:
  SingleProducerSingleConsumerFixedSizeQueue(int max_size)
    : max_size_(max_size),
      buffer_(new Entry[max_size]),
      head_(0),
      tail_(0) {
    /* Needs to be updated */      
    for (int i = 0; i < max_size; ++i) {
      buffer_[i].valid = false;
    }
  }

  ~SingleProducerSingleConsumerFixedSizeQueue() {
    delete[] buffer_;
  }

  virtual bool Read(T* w) {
    /* Needs to be updated */      
      return true;
  }

  virtual bool Write(const T& w) {
    /* Needs to be updated */      
      return true;
  }

  bool isEmpty() {
      if (head_ == tail_ && !buffer_[tail_].valid) 
          return true;
      else
          return false;
  }

 private:
  struct Entry {
    T data;
    bool valid; 
  };

  int max_size_;
  Entry* buffer_;
  int head_ __attribute__((aligned(64)));
  int tail_ __attribute__((aligned(64)));
};


// Implements a fixed-size queue using no lock, but limited to a single
// producer thread and multiple consumer threads.
template<typename T>
class SingleProducerMultipleConsumerFixedSizeQueue : public FixedSizeQueueInterface<T> {
 public:
  SingleProducerMultipleConsumerFixedSizeQueue(int max_size)
    : max_size_(max_size),
      buffer_(new Entry[max_size]),
      head_(0),
      tail_(0) {
    /* Needs to be updated */      
    for (int i = 0; i < max_size; ++i) {
      buffer_[i].valid = false;
    }
  }

  ~SingleProducerMultipleConsumerFixedSizeQueue() {
    delete[] buffer_;
  }

  virtual bool Read(T* w) {
    /* Needs to be updated */      
      return true;
  }

  virtual bool Write(const T& w) {
    /* Needs to be updated */      
      return true;
  }

  bool isEmpty() {
      if (head_ == tail_ && !buffer_[tail_].valid) 
          return true;
      else
          return false;
  }

 private:
  struct Entry {
    T data;
    bool valid; 
  };

  int max_size_;
  Entry* buffer_;
  int head_ __attribute__((aligned(64)));
  int tail_ __attribute__((aligned(64)));
};


// Implements a fixed-size queue using no lock, but limited to multiple 
// producer threads and a single consumer thread.
template<typename T>
class MultipleProducerSingleConsumerFixedSizeQueue : public FixedSizeQueueInterface<T> {
 public:
  MultipleProducerSingleConsumerFixedSizeQueue(int max_size)
    : max_size_(max_size),
      buffer_(new Entry[max_size]),
      head_(0),
      tail_(0) {
    /* Needs to be updated */      
    for (int i = 0; i < max_size; ++i) {
      buffer_[i].valid = false;
    }
  }

  ~MultipleProducerSingleConsumerFixedSizeQueue() {
    delete[] buffer_;
  }

  virtual bool Read(T* w) {
    /* Needs to be updated */      
      return true;
  }

  virtual bool Write(const T& w) {
    /* Needs to be updated */      
      return true;
  }

  bool isEmpty() {
      if (head_ == tail_ && !buffer_[tail_].valid) 
          return true;
      else
          return false;
  }

 private:
  struct Entry {
    T data;
    bool valid; 
  };

  int max_size_;
  Entry* buffer_;
  int head_ __attribute__((aligned(64)));
  int tail_ __attribute__((aligned(64)));
};


#endif  // QUEUES_H_
