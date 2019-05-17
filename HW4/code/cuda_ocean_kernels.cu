


#ifdef VERSION1
__global__ void ocean_kernel(int *grid, int xdim, int ydim, int offset)
{
    int threads = gridDim.x*blockDim.x;
    int threadId  = blockDim.x*blockIdx.x + threadIdx.x;

    if (threads > (xdim-2)*(ydim-2)) {
        threads = (xdim-2)*(ydim-2);
        if (threadId >= threads) {
            return;
        }
    }

    int chunk = (xdim-2)*(ydim-2)/threads;
    int start = threadId * chunk;
    int end = (threadId + 1) * chunk;

    int threadsPerRow = (xdim - 2);

    for (int i=start; i<end; i++) {
        if (offset) {
            if (i%2) continue;
        } else {
            if (!(i%2)) continue;
        }

        int row = i / threadsPerRow;
        int col = i % threadsPerRow;

        int loc = xdim + row * xdim + col;
        if (offset) {
            loc += (row%2) ? 1 : 0;
            loc += 1;
        } else {
            loc += (row%2) ? 0 : 1;
        }
        // printf("Row: %d, Col: %d\n", row, col);
        // printf("loc: %d\n", loc);

        grid[loc] = (grid[loc]
                  + grid[loc - xdim]
                  + grid[loc + xdim]
                  + grid[loc + 1]
                  + grid[loc - 1])
                  / 5;
    }
}
#endif


#ifdef VERSION2
__global__ void ocean_kernel(int *grid, int xdim, int ydim, int offset)
{

    // Your code for task 2
    
        
}
#endif

#ifdef VERSION3

__global__ void split_array_kernel(int *grid, int *red_grid, int *black_grid, int xdim, int ydim)
{
    // This kernel should take the contents of grid and copy all of the red
    // elements into red_grid and all of the black elements into black_grid
}

__global__ void unsplit_array_kernel(int *grid, int *red_grid, int *black_grid, int xdim, int ydim)
{
    // This kernel should take the red_grid and black_grid and copy it back into grid
}

__global__ void ocean_kernel(int *red_grid, int *black_grid, int xdim, int ydim, int offset)
{
    // Your code for task 3
}
#endif
