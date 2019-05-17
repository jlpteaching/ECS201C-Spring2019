#include <stdio.h>

#define VERSION1
//#define VERSION15
//#define VERSION2
//#define VERSION3

#include "cuda_ocean_kernels.cu"

void Check_CUDA_Error(const char *message)
{
   cudaError_t error = cudaGetLastError();
   if(error!=cudaSuccess) {
      fprintf(stderr,"ERROR: %s: %s\n", message, cudaGetErrorString(error) );
      exit(-1);
   }
}

extern "C++"
void ocean (int **grid, int xdim, int ydim, int timesteps)
{
    /********************* the red-black algortihm (start)************************/
    /*
    In odd timesteps, calculate indeces with - and in even timesteps, calculate indeces with *
    See the example of 6x6 matrix, A represents the corner elements.
        A A A A A A
        A - * - * A
        A * - * - A
        A - * - * A
        A * - * - A
        A A A A A A
    */

    // Set up the GPU datastructure used in the first 3 kernel verisons

    int *d_grid;

    cudaMalloc(&d_grid, sizeof(int)*xdim*ydim);
    Check_CUDA_Error("malloc grid failed");

    cudaMemcpy(d_grid, &grid[0][0], xdim*ydim*sizeof(int), cudaMemcpyHostToDevice);
    Check_CUDA_Error("memcpy grid to device failed");

    #if defined(VERSION3)

    // set up the GPU datastructure for the other kernel versions
    int *red_grid, *black_grid;
    cudaMalloc(&red_grid, sizeof(int)*xdim*ydim / 2);
    Check_CUDA_Error("malloc red_grid failed");
    cudaMalloc(&black_grid, sizeof(int)*xdim*ydim / 2);
    Check_CUDA_Error("malloc black_grid failed");

    split_array_kernel<<<16,512>>>(d_grid, red_grid, black_grid, xdim, ydim);
    Check_CUDA_Error("split_array_kernel launch failed");

    #endif

    dim3 gridDim(16,1,1);
    dim3 blockDim(128,1,1);

    for (int ts=0; ts<timesteps; ts++) {
        #if defined(VERSION3)
        ocean_kernel<<<gridDim, blockDim>>>(red_grid, black_grid, xdim, ydim, ts%2);
        #else
    	ocean_kernel<<<gridDim, blockDim>>>(d_grid, xdim, ydim, ts%2);
        #endif
    	Check_CUDA_Error("ocean_kernel launch failed");
    }

    #if defined(VERSION3)
    unsplit_array_kernel<<<16,512>>>(d_grid, red_grid, black_grid, xdim, ydim);
    Check_CUDA_Error("unsplit_array_kernel launch failed");
    #endif

    cudaMemcpy(&grid[0][0], d_grid, xdim*ydim*sizeof(int), cudaMemcpyDeviceToHost);
    Check_CUDA_Error("memcpy grid back failed");

    cudaFree(d_grid);


    /////////////////////// the red-black algortihm (end) ///////////////////////////
}
