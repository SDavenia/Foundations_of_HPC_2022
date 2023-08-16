#if defined(__STDC__)
#  if (__STDC_VERSION__ >= 199901L)
#     define _XOPEN_SOURCE 700
#  endif
#endif
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int nrow = 10; 
    int ncol = 10;

    double* ptr;
    ptr = (double*)malloc(sizeof(double) * nrow * ncol);

    free(ptr);
}


