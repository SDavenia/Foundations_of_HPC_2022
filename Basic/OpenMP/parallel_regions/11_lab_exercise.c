#if defined(__STDC__)
#  if (__STDC_VERSION__ >= 199901L)
#     define _XOPEN_SOURCE 700
#  endif
#endif
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
/*
Code to obtain the Mandelbrot set in the interval delimited by bottom left corner (-1.5, -1) and right corner (0.5, 1).
The code takes as command-line arguments nrow, ncol, Imax
*/

int main(int argc, char* argv[])
{
    int nrow = 10;  // nx, ny : number of points to consider in the interval
    int ncol = 10;
    int Imax = 100; 

    if(argc > 1){
        if(argc==4){
            nrow = atoi(argv[1]);
            ncol = atoi(argv[2]);
            Imax = atoi(argv[3]);
            printf("nrow=%d, ncol=%d, Imax=%d.\n", nrow, ncol, Imax);
        }
        else
            printf("Wrong number of inputs, the default will be used.\n");
    }



    // Points determining the delimiters of the region
    double xL = -1.5;
    double yL = -1;
    double xR = 0.5;
    double yR = 1;

    // Pointer to the allocated matrix containing whether the pixel is in the Mandelbrot set (1) or not (0).
    int* ptr;
    ptr = (int*)malloc(sizeof(int) * (nrow+1) * (ncol+1)); // +1 is so that xR is included in the set for computation

    double dx = (xR - xL)/(double)nrow;
    double dy = (yR - yL)/(double)ncol;

    // Compute for all the entries in the matrix
    for(int i = 0; i <= nrow; i++){
        for(int j = 0; j <= ncol; j++){

            double c_real = xL + dx * j; 
            double c_im = yR - dy * i;

            // printf("(%f, %f)\n", c_real, c_im);

            // To store the local computations
            double z_real = 0;
            double z_im = 0;

            double abs2=0;
            for(int k = 0; k < Imax; k++){
                // Update
                double temp_real = z_real;
                double temp_im = z_im;

                // Update z_real and z_im
                z_real = temp_real * temp_real - temp_im * temp_im + c_real;
                z_im = 2 * temp_real * temp_im + c_im;

                // Check whether we can stop the loop
                abs2 = z_real * z_real + z_im * z_im;
                if (abs2 >= 4){ 
                    break; // If this condition is met it is not in the Mandelbrot set
                }
            }
            int value;
            value = abs2 < 4 ? 1 : 0; // If it is less than 4 it is in the Mandelbrot set, else it is not.
            ptr[i + ncol*j] = value;
        }
    }


    printf("Printing matrix of points in the set\n");
    
    for(int i = 0; i <=nrow; i++){
        for(int j=0; j <=ncol; j++){
            printf("%d ", ptr[i + ncol*j]);
        }
        printf("\n");
    }    
    free(ptr);  


}


