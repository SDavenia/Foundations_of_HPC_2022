#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(int argc, char **argv)
{
    int nrows = 3;
    int ncols = 3;

    int (*matrix)[ncols] = calloc(nrows * ncols, sizeof(*matrix));
    printf("Size of (*matrix) is %lu\n", sizeof(*matrix));
    printf("matrix contains %p\n", matrix);

    for(int i = 0; i < ncols; i++){
        printf("Matrix[%d] contains %p\n", i, matrix[i]);
    }



    
}