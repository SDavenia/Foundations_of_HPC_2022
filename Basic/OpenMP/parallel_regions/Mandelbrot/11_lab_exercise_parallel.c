#if defined(__STDC__)
#  if (__STDC_VERSION__ >= 199901L)
#     define _XOPEN_SOURCE 700
#  endif
#endif
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <omp.h>

/*
Code to obtain the Mandelbrot set in the interval delimited by bottom left corner (-1.5, -1) and right corner (0.5, 1).
The code takes as command-line arguments nrow, ncol, Imax
*/


#if defined(_OPENMP)
#define CPU_TIME ({struct  timespec ts; clock_gettime( CLOCK_REALTIME, &ts ),\
					  (double)ts.tv_sec +		\
					  (double)ts.tv_nsec * 1e-9;})

#define CPU_TIME_th ({struct  timespec myts; clock_gettime( CLOCK_THREAD_CPUTIME_ID, &myts ),\
					     (double)myts.tv_sec +	\
					     (double)myts.tv_nsec * 1e-9;})
#else

#define CPU_TIME ({struct  timespec ts; clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &ts ),\
					  (double)ts.tv_sec +		\
					  (double)ts.tv_nsec * 1e-9;})

#endif

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
    
    double dx = (xR - xL)/(double)nrow;
    double dy = (yR - yL)/(double)ncol;

    // Pointer to the allocated matrix containing whether the pixel is in the Mandelbrot set (1) or not (0).
    int* ptr;
    int nthreads = 1;

    #pragma omp parallel
    #pragma omp master
        nthreads = omp_get_num_threads();

    printf("Code will be executed with %d threads\n", nthreads);



    ptr = (int*)malloc(sizeof(int) * (nrow+1) * (ncol+1)); // +1 is so that xR is included in the set for computation
    // ptr = (int*)calloc((nrow+1)*(ncol+1), sizeof(int));

    double tstart      = CPU_TIME;                         // take the time for th 0
    #pragma omp parallel
    {
        #pragma omp for collapse(2)
        for(int i = 0; i <= nrow; i++){
            for(int j = 0; j <= ncol; j++){

                //printf("i = %d, j= %d, threadId = %d \n", i, j, omp_get_thread_num());


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
                value = (abs2 < 4); // If it is less than 4 it is in the Mandelbrot set, else it is not.
                ptr[i + ncol*j] = value;
            }
        }
    }
    
    double tend      = CPU_TIME;     
    printf("Process took %g of wall-clock time\n", tend - tstart );
/*
    printf("Printing matrix of points in the set\n");
    
    for(int i = 0; i <=nrow; i++){
        for(int j=0; j <=ncol; j++){
            printf("%d ", ptr[i + ncol*j]);
        }
        printf("\n");
    }    
*/

    free(ptr);  

}


