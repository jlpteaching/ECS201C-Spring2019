
# Homework 4

Note: This homework is a modified version of an assignment from [CS 758 at University of Wisconsin-Madison](http://pages.cs.wisc.edu/~david/courses/cs758/Fall2016/wiki/index.php?n=Main.Homework7).

## DUE Thursday 5/23 before class (10:30am)

Useful links:

  - [Introduction to CUDA](https://devblogs.nvidia.com/even-easier-introduction-cuda/)
  - [NVIDIA Turing Architecture](https://devblogs.nvidia.com/nvidia-turing-architecture-in-depth/)
  - [Nsight Compute CLI](https://docs.nvidia.com/nsight-compute/NsightComputeCli/index.html)

The purpose of this assignment is to familiarize yourself with GPGPU computing platforms (CUDA) and to gain experience with GPGPU specific optimizations. For this assignment you will be given a basic implementation of an algorithm which runs on the GPU and you will procedurally improve it applying GPGPU optimization principles.

You are supposed to use "Crystal" to get your code working for the final speedups and other results.
Your accounts will be setup on the machine.
You can ssh with your kerberos user ID.
(I.e., ssh [username]@crystal.cs.ucdavis.edu).
However, your password is different.
See the teams channel for details.
Let Ayaz know via email or teams if you do not have an account.

**Important: When using crystal, be sure to consider other users.**

1. This is a research machine used by students in the DArchR research group and beyond.
2. Other people in the class may be conducting experiments.

Follow these simple guidelines:

- Before running an experiment, check to see if anyone else is running an experiment with `top`. If you see a version of `ocean` running, wait a few minutes.
- Don't let your tests run for too long. Any single test should not take more than 5 minutes.

Any questions about crystal should be posted on the Teams portal.

## The Problem

For this assignment you will again be implementing the Ocean algorithm. For more information see [Homework 1](https://github.com/jlpteaching/ECS201C/blob/master/HW1/HW1.md). You will be comparing the performance of your GPU-optimized algorithm to your solution from Homework 1. A simple solution to homework 1 is also included in the template files feel free to use it if you want.


## The Hardware

You will be using Crystal which contains a Nvidia 2080-TI GPU (with 11GB GDDR5), which is based on NVIDIA [Turing](https://devblogs.nvidia.com/nvidia-turing-architecture-in-depth/) architecture.


## Profiling
You can use an application called computeprof provided with CUDA to profile your workloads. Computeprof does a good job of concisely representing the performance counters available on the NVidia GPUs. To use this program, you will need to use "ssh -X" to login to the Crystal machine in order to forward the X server. You can then run it using "/usr/local/cuda-10.0/bin/computeprof". You can use computeprof to diagnose the bottlenecks in each implementation of the algorithm.
Another option is to use one of the new profling tools available with CUDA called Nsight Compute CLI (command line tool) and Nsight Compute (UI). You can run it using "/usr/local/cuda-10.0/NsightCompute-1.0/nv-nsight-cu" on Crystal.


## Task 1: Write an OpenACC version of Ocean.
[OpenACC](https://www.openacc.org/) is another programming standard for parallel computing. You are supposed to make use of OpenACC compiler directives to write a version of this algorithm that can then be offloaded to an accelerator (GPU in this case).

**NOTE:** This should be very easy. You can simply take the OMP version of the code given and change the pragma.
  
  - Question a) How does this version compare in performance compared to the OMP version for same input sizes?
  - Question b) How will you compare both versions in terms of programmer effort?

## Task 2: Porting the CPU algorithm
There is a baseline implementation of the ocean_kernel in the template files. It is available in cuda_ocean_kernels.cu after #ifdef VERSION1. Although considerably more verbose, this is a mostly literal translation of the algorithm in omp_ocean.cpp with OpenMP static partitioning. Each thread gets a chunk of locations within the red/black ocean grid and updates those locations. Study this code and be sure to understand how it works.

**NOTE:** This should be very easy. We've already written the code for you!

  - Question a) Describe memory divergence and why it leads to poorly performing code in the SIMT model.
  - Question b) Describe the memory divergence behavior of VERSION1 of ocean_kernel.
  - Question c) Vary the block size / grid size. What is the optimal block / grid size for this implementation of ocean? What is the speedup over 1 block and 1 thread ("single threaded")? Run with an input of 16384 16384 1000.
  - Question d) What is the speedup over the single threaded CPU version? Run with an input of 16384 16384 1000.
  
 
 ## Task 3: Reduce memory divergence (Convert algorithm to "SIMD")
Implement VERSION2 of ocean_kernel. This version of the kernel will take a step towards reducing the memory divergence. Instead of giving each thread a chunk of the array to work on, re-write the algorithm so that the threads in each block work on adjacent elements (i.e. for a red iteration, thread 0 will work on element 0, thread 1 will work on element 2, thread 3 will work on element 6, etc).

**NOTE:** This should also be very easy. If you are finding this part is taking >30 minutes to code, ask for help :).

  - Question a) Describe where memory divergence still exists in this implementation of ocean.  
  - Question b) Vary the block size / grid size. What is the optimal block / grid size for this implementation of ocean?
  - Question c) How does this version compare to VERSION1? Run with the optimal block sizes for each respectively and an   input of 16384 16384 1000.
  
 ## Task 4: Further reduce memory divergence (Modify data structure to be GPU-centric).
Implement VERSION3 of ocean_kernel. Instead of using one flat array to represent the ocean grid, split it into two arrays, one for the red cells and one for the black cells. You should start by writing two other kernels which will split the grid object into red_grid and black_grid and take red/black_grid and put them back into the grid object.

Feel free to add any other optimizations to this implementation. Just describe them in your write-up.
One suggested optimization: Implement tiling in your thread blocks.
Instead of assigning a subset of a row to each thread block, assign a 2D tile of cells.
You may even be able to use scratchpad memory (`__shared_memory__` or something like that) to further speed up the computation.
Can you combine the splitting of the arrays and the use of scratchpad? Hmm...

**NOTE:** This is the part you should spend the most time on! Hopefully, you've spent less than an hour getting to this point.

  - Question a) How does the performance of this version compare to VERSION2? Is this what you expected?
  - Question b) Time each kernel and the memory copies separately (ocean_kernel, and (un)split_array_kernel). Which actions are taking the most execution time? How does this affect the overall execution time of the algorithm? (computeprof does a good job summarizing this data)
  - Question c) Vary the block size / grid size. What is the optimal block / grid size for this implementation of ocean? Does it change when you change the problem size?
  - Question d) Describe branch divergence and why it leads to poorly performing code in the SIMT model. Does your code exhibit any branch divergence? If so, where?
  - Question e) Run either your OpenMP version of ocean or the one in the template files. How does the performance of the CPU version of Ocean compare to the GPU version, better or worse? Why do you think this is? Run with different problem sizes.
  - Question f) What do you think of CUDA? SIMT programming in general? How does OMP, OpenACC, and CUDA programming compare?

## What to Hand In:

[Via canvas](...)
 - A *pdf* file with your answers to the above questions.
 - A gzipped tarball (e.g., `code.tgz`) with the code you used to answer the questions.

**You are expected to complete the assignment individually.**
However, you may discuss your solutions, your results (at a high level, not in detail), CUDA best practices, etc. with one another.
**The code and answers to the questions must be completed individually.**
Feel free to use the class [Teams team](https://teams.microsoft.com/l/team/19%3ad6420d6da2ef421fb15ba63709562467%40thread.skype/conversations?groupId=077efc54-af37-496e-9405-8c7783fa2d3e&tenantId=a8046f64-66c0-4f00-9046-c8daf92ff62b) to discuss as well.
  
## Tips and Tricks:
  
   - Start early.
   - Run your programs multiple times (two or three times will do for the long running tests) to get accurate time measurements. This will help avoid incorrect results due to interference with other user's programs.
   - While making your measurements do take care that no-one else is running their program on the machine. Otherwise, it will provide you as well as the other person wrong results as well as longer runtimes.
   - Do not wait until the last day to run the experiments. You might not get time on the machine to get good results.
   - You may want to [set up ssh keys](http://csifdocs.cs.ucdavis.edu/about-us/csif-general-faq#TOC-How-do-I-set-up-SSH-keys-to-allow-me-to-login-to-the-CSIF-computers-without-a-password-) to save yourself some keystrokes by not having to type in your password every time.
