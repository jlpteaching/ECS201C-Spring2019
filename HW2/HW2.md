
# Homework 2: Lock-free Queues

Note: This homework is a modified version of an assignment from [CS 758 at University of Wisconsin-Madison](http://pages.cs.wisc.edu/~david/courses/cs758/Fall2016/wiki/index.php?n=Main.Homework5).

## DUE 4/30 at 10:30am (before class)

## IMPORTANT HINTS

### Useful links:

  - [C++ memory_order reference](https://en.cppreference.com/w/cpp/atomic/memory_order)
  - [Herb Sutter’s atomic weapons](https://channel9.msdn.com/Shows/Going+Deep/Cpp-and-Beyond-2012-Herb-Sutter-atomic-Weapons-1-of-2)
  - [Scott Synthesis12](https://www.morganclaypool.com/doi/abs/10.2200/S00499ED1V01Y201304CAC023?journalCode=cac)
  - [Introduction to Lock-Free Programming](https://preshing.com/20120612/an-introduction-to-lock-free-programming/)

### Work together!

Getting this kind of concurrency right is **hard**.
Use your classmates as a helpful resource when trying to derive the solutions.

Feel free to discuss algorithms, specific code examples, etc. with one another on Teams or via other venues.
You may even discuss the results you are getting to see if others are getting similar data.
However, in the end, you must write your own code and do your own write up of the questions.

### Start early!

Enough said?
This assignment is significantly harder than the previous assignment.
You will need to put some time into learning about C++ atomics.

## Introduction

The purpose of the assignment is to give you experience optimizing parallel code using C++ synchronization mechanisms (including "C++11 atomics"). This exercise is intended to allow you to play with some classic locking techniques as well as newer lock-free methods in a simple yet challenging task. Hopefully, this will give you an idea about the subtleties and complexities involved in writing larger and more complex programs using these techniques.

You are supposed to use the amarillo machine to get your code working for the final speedups and other results.

**Important: When using amarillo, be sure to consider other users.**

1. This is a research machine used by students in the DArchR research group and beyond.
2. Other people in the class may be conducting experiments.

Follow these simple guidelines:

- Before running an experiment, check to see if anyone else is running an experiment with `top`. If you see a version of `test` running, wait a few minutes.
- Don't let your tests run for too long. Most tests should finish in < 1 minute and all tests should finish in < 5 minutes.
- If you see `gem5` processes running for a long period of time, let Jason know via Teams. We'll ask the current amarillo users to hold off on executing and long-running jobs.

Any questions about amarillo should be posted on the Teams portal.

## Lock-free Programming

Lock-free techniques are supported in C++11 by the introduction of atomic\<T\>, which use platform-specific operations (think Load-Linked/Store Conditional or atomic Fetch-and-Add) to guarantee atomic reads and writes for atomic types. Additionally, an atomic compare/exchange method is introduced to allow publishing of updates.

```
template< class T > bool atomic_compare_exchange_*( std::atomic<T>* obj,T* expected, T desired );
```

You'll likely want to read up a bit on the [C/C++ memory model](https://en.cppreference.com/w/cpp/language/memory_model) before digging into the lock-free implementations.
Specifically, you'll want to make sure your program has no data races [as defined by the C++ specification](https://en.cppreference.com/w/cpp/language/memory_model#Threads_and_data_races):

> When an evaluation of an expression writes to a memory location and another evaluation reads or modifies the same memory location, the expressions are said to conflict. A program that has two conflicting evaluations has a data race unless
> - both evaluations execute on the same thread or in the same signal handler, or
> - both conflicting evaluations are atomic operations (see std::atomic), or
> - one of the conflicting evaluations happens-before another (see std::memory_order)

To accomplish this in your lock-free design, you will want to make sure that all variables/data shared between threads are `std::atomic` types.
I suggest you then explicitly use `load()` and `store()` functions when accessing these variables.
This will make debugging easier, and it will also make it easier when you try to implement accessing with more relaxed consistency models.


## Programming Task: Fixed Size Queue

In this assignment, we expect you to implement a fixed sized queue with the following interface:

```
template<typename T> class FixedSizeQueueInterface {
 public:
  virtual ~FixedSizeQueueInterface() { }
  virtual bool Read(T* data) = 0;
  virtual bool Write(const T& data) = 0;
};
```

To start you off, we provide you with a sample mutex-based queue implementation (MX) of the above queue interface (in queue.h), and a benchmarking program to evaluate the performance of queues with the above interface. Your job is to optimize the implementation using the following techniques -

1. Develop a queue implementation with fine-grained locks (FG).
2. Develop a lock-free circular queue implementation which works with a single producer and a single consumer (LF1).
3. Develop a lock-free circular queue implementation which works with a single producer and a multiple consumers (LF2).
4. Develop a lock-free circular queue implementation which works with a multiple producers and a single consumer (LF3).

## Template for your convenience for HW5

A [template](code) is provided for your convenience with the basic setup of the program. This template provides you the initialized queue interface to work with, and the skeleton for the other implementations. You are free to change the benchmarking program for your own purposes, but your code will be checked by programs which assume you adhere to the interfaces provided. A makefile has also been added to the template that will help you in compiling the code. You might need to change the flags in the makefile during debug phase. Do revert them back to allow compiler optimizations.

Download the template from [here](code).
  - queues.h contains the mutex-based queue implementation, as well as skeletons of other implementations for you to fill out. This is where your code will go.
  - test.cc is the benchmarking program, which needs to be modified slightly as you add newer implementations, and is invoked thus-

  ```
  ./test <num_iterations> <producer_threads> <consumer_threads>
  ```

The number of producer threads is only used for the mutex and the LF3, while the number of consumer threads is used for the mutex and LF2. The benchmarking program runs the tests for a given number of iterations, and averages the throughput. Some useful macros and test parameters are provided at the beginning of test.cc.

We have added a few asserts to help you keep a couple of invariants.
We found these invariants helpful when debugging as we were creating/updating this assignment.

1. The head pointer should always be greater than or equal to the tail pointer.
2. When reading, the node should always be valid, and when writing the node pointer should always be invalid.

You may want to add more asserts for other invariants you find useful when debugging.
Feel free to let your classmates know what invariants are useful.

**NOTE:** You should remove these debugging asserts when running your tests!

## Problem 1: Utilize fine-grained Locks

Write a version of the fixed-sized queue with fine-grained locks using std::mutex. To achieve this, your implementation needs to have one lock per element of the queue, instead of using one BIG lock for the whole queue. Feel free to move the declaration of kMaxQueueSize=1000 to the file queues.h from test.cc. You will need this to declare a fixed size array of mutexes. For simplicity, you may assume that the number of producer or consumer threads are always in powers of two, and that the total number of operations is always divisible exactly by the number of producers/consumers.

### Hints
 - You can add new data structures to the code and/or modify current data structures, if needed. You only need to keep the interface the same (so it works with the test code).
 - You can put a mutex as part of the `Entry` class.
 - Remember what is local to one thread and what is globally visible.

### Questions

1. Provide a couple of sentences in the final write-up describing how you convinced yourself your algorithm was implemented correctly.

## Problem 2: Use Lock-free programming

For this problem, you will use lock-free techniques to implement a circular fixed-sized queue. As lock-free programming can be rather tricky, you will do this in stages.

The first part is (almost) straightforward. You can start by creating a regular circular queue, and then identifying the variables shared between the producer and the consumer threads. These need to be atomically updated in a way which guarantees consistent updates of the queue. Finally, develop tests to check that there are no data races even in the absence of locks. Verifying that an implementation works is usually more difficult than creating the implementation in the first place. You could try out extreme conditions - making the queue size as 1 for instance would help you locate tricky conditions more easily.

  - Develop a lock-free circular queue implementation which works with a single producer and a single consumer (LF1).
  - Develop a lock-free circular queue implementation which works with a single producer and multiple consumers (LF2).
  - Develop a lock-free circular queue implementation which works with multiple producers and a single consumer (LF3).

As you are working, try to understand how the constraints on the queue - fixed size and circular, help your case for the lock-free implementations. Also, **if you do not manage to get these working correctly, an analysis of what error is occurring** (for instance the ABA problem) will get you partial credit.

For simplicity, you may assume that the number of producer or consumer threads are always in powers of two , and that the total number of operations is always divisible exactly by the number of producers/consumers (**you will get errors if they are not**).

### Questions

2. Describe your implementations for each of the above queues.
3. Describe at least 2 notable examples of tricky scenarios you encountered while writing the lock-free implementations.
4. Provide a couple of sentences in the final writeup describing how you convinced yourself your algorithm was implemented correctly. Describe how the queue constraints simplify your program.

### Hints

 - Debugging multithreaded programs is a pain. Some suggestions
   - Use asserts, not print-based debugging when you can
   - When you do use print-based debugging use a [string stream](https://en.cppreference.com/w/cpp/io/basic_stringstream) to save the info you want print and dump it all at once with (`std::cout << stream.str();`)
 - Testing with very small queue sizes (e.g., 1 or 10) often causes problems faster
 - Ask for help if you are stuck! This is what office hours and the Teams is for!

#### LF1

 - You don't need any fancy atomic operations
 - You may want to use [C++ `atomic` variables](https://en.cppreference.com/w/cpp/atomic/atomic) and use the `load()` and `store()` functions. This may or may not be required ;).

#### LF2
 - You will likely want to use [C++ `atomic` variables](https://en.cppreference.com/w/cpp/atomic/atomic) and [atomic compare and exchange](https://en.cppreference.com/w/cpp/atomic/atomic/compare_exchange) functions.
 - For now, ignore the memory order options and assume sequential consistency (`std::memory_order_seq_cst`).

#### LF3
 - The solution to this problem should be *very* similar to the solution to LF2

## Problem 3: Analysis of Fixed Size Queues

For this analysis, set the number of operations as 10000000, queue size as 1000, and run each experiment for 5 iterations. For each graph, make sure the axes are named correctly, have title, captions and legends as needed, and in general, are self-sufficient. Use only std::memory_order_seq_cst for this portion.

### Questions

5. Compare the throughput of all 5 queue implementations (MX - provided, FG, LF1, LF2, LF3) for a single producer, single consumer scenario. If you LF version is faster (or slower), describe why you think this is.
7. Compare the throughput of MX, FG, LF2 for a single producer, multiple consumer case with number of consumer threads = [1,2,4,8,16,24,48]
8. Compare the throughput of MX, FG, LF3 for a multiple producer, single consumer case with number of producer threads = [1,2,4,8,16,24,48].

9. Repeat this experiment (#7 and #8) on an ARM machine (graviton) for threads=[1,2,4,8,16]. [To Add: Details of AWS accounts]

## Problem 4: Analysis with different memory models

For this analysis, set the number of operations as 10000000, queue size as 1000, and run each experiment on amarillo and graviton for 5 iterations. For each graph, make sure the axes are named correctly, have title, captions and legends as needed, and in general, are self-sufficient.

9. Compare the throughput of all 3 lockfree queue implementations (LF1, LF2, LF3) for a single producer, single consumer scenario using both std::memory_order_seq_cst and std::memory_order_acquire/release.


## What to Hand In:

[Via canvas](...)
 - A *pdf* file with your answers to the above questions (there are 9 above).
 - A gzipped tarball (e.g., `code.tgz`) with the code you used to answer the questions.

**You are expected to complete the assignment individually.**
However, you may discuss your solutions, your results (at a high level, not in detail), etc. with one another.
**The code and answers to the questions must be completed individually.**
Feel free to use the class [Teams team](https://teams.microsoft.com/l/team/19%3ad6420d6da2ef421fb15ba63709562467%40thread.skype/conversations?groupId=077efc54-af37-496e-9405-8c7783fa2d3e&tenantId=a8046f64-66c0-4f00-9046-c8daf92ff62b) to discuss as well.
