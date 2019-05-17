#include <chrono>
#include <cstdlib>
#include <iostream>

using namespace std;

/* Implement this function in serial_ocean and omp_ocean */
extern void ocean (int** grid, int xdim, int ydim, int timesteps);

void printGrid(int** grid, int xdim, int ydim);

int main(int argc, char* argv[])
{
    int xdim,ydim,timesteps;
    int** grid;
    int i,j,t;


    /********************Get the arguments correctly (start) **************************/
    /*
    Three input Arguments to the program
    1. X Dimension of the grid
    2. Y dimension of the grid
    3. number of timesteps the algorithm is to be performed
    */

    if (argc!=4) {
        printf("The Arguments you entered are wrong.\n");
        printf("./ocean <x-dim> <y-dim> <timesteps>\n");
        return EXIT_FAILURE;
    } else {
        xdim = atoi(argv[1]);
        ydim = atoi(argv[2]);
        timesteps = atoi(argv[3]);
    }
    ///////////////////////Get the arguments correctly (end) //////////////////////////


    /*********************create the grid as required (start) ************************/
    /*
    The grid needs to be allocated as per the input arguments and randomly initialized.
    Remember during allocation that we want to gaurentee a contiguous block, hence the
    nasty pointer math.

    To test your code for correctness please comment this section of random initialization.
    */
    grid = (int**) malloc(ydim*sizeof(int*));
    int *temp = (int*) malloc(xdim*ydim*sizeof(int));
    for (i=0; i<ydim; i++) {
        grid[i] = &temp[i*xdim];
    }
    for (i=0; i<ydim; i++) {
        for (j=0; j<xdim; j++) {
            //grid[i][j] = rand();
            if (i == 0 || j == 0 || i == ydim-1 || j == xdim-1) {
             grid[i][j] = 1000;
            } else {
             grid[i][j] = 0;
            }
        }
    }
    ///////////////////////create the grid as required (end) //////////////////////////

   
    chrono::milliseconds total_time;
    auto start = chrono::high_resolution_clock::now(); // Start the time measurment here before the algorithm starts
    //printGrid(grid, xdim, ydim);

    ocean(grid, xdim, ydim, timesteps);


	total_time = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start);  // End the time measuremnt here since the algorithm ended
    cout << "Total Execution time: "  << total_time.count() << "ms" << endl; // print the execution time in ms
    
    // Free the memory we allocated for grid
    free(temp);
    free(grid);

    return EXIT_SUCCESS;
}

void printGrid(int** grid, int xdim, int ydim)
{
    for (int i=0; i<xdim; i++) {
        for (int j=0; j<ydim; j++) {
            printf("%05d  ", grid[i][j]);
        }
        printf("\n");
    }
}
