#include <stdio.h>

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

    // PUT YOUR CODE HERE
    for (int ts=0; ts<timesteps; ts++) {
        for(int i=1; i<xdim-1; i++) {
            int offset = (i+ts)%2;
            for(int j=1+offset; j<ydim-1; j+=2) {
                grid[i][j] = (grid[i][j] + grid[i-1][j] + grid[i+1][j]
                                + grid[i][j-1] + grid[i][j+1])/5;
            }
        }
    }
    /////////////////////// the red-black algortihm (end) ///////////////////////////
}
