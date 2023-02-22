#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(int argc, char **argv)
{
    int nrows = 3;
    int ncols = 3;

    // With malloc we return a pointer to the allocated space
    // As such here we will return a pointer to pointer to int.
    // ptr = (cast-type*) malloc(byte-size)

    int **matrix = (int**)malloc((nrows + ncols) * sizeof(int*)); 
    // This way we allocate (nrows + ncols) pointers to int (int*)

    // Now we create a new pointer pointing to same memory location as matrix but after nrows.
    int **tmatrix = matrix + nrows;  // Create a new pointer pointing to same memory location but after nrows pointers

    //printf("size of matrix is %lu\n", sizeof(matrix)); // pointer so 8B
    //printf("Memory pointed by matrix is %p and tmatrix is %p\n", matrix, tmatrix);  // We can see they are distanced by 8*3 B (pointer arithmetic)  
    
    // We create an array of integers all (pointer to int) where we have the data which will be used to fill in our matrix
    // Since we use calloc, it will be all zeros.
    // All contains elements for 2 n x n matrices
    int* all = (int*)calloc(2*nrows*ncols, sizeof(int)); 
    //printf("all points to %p\n", all);
    
    // Here we initialize each element of matrix to the first half of all
    // matrix[i] is a pointer to int, so we allocate it to a memory address (all + i*ncols), not to a numeric value.
    // Since matrix[i] is a pointer to int if we dereference it we get an int (see below), in this case 0 since we used calloc.
    for(int i = 0; i < nrows; i++){
        matrix[i] = all + i*ncols; // all is a pointer to int (8B) 
        //printf("Memory address stored in matrix[%d] is %p\n",i, matrix[i]);
        //printf("It contains %d\n", *matrix[i]);
    }
    
    // We also initialize the transpose t to the second half of all (note we add nrows * ncols)
    // We store tmatrix so that its columns elements are adjacent (notice + i*nrows, so each one should fit a whole row).
    for(int i = 0; i < ncols; i++){
        tmatrix[i] = all + nrows * ncols + i * nrows;
    }



    
}