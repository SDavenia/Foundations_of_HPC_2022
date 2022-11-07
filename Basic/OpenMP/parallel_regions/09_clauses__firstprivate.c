
/* ────────────────────────────────────────────────────────────────────────── *
 │                                                                            │
 │ This file is part of the exercises for the Lectures on                     │
 │   "Foundations of High Performance Computing"                              │
 │ given at                                                                   │
 │   Master in HPC and                                                        │
 │   Master in Data Science and Scientific Computing                          │
 │ @ SISSA, ICTP and University of Trieste                                    │
 │                                                                            │
 │ contact: luca.tornatore@inaf.it                                            │
 │                                                                            │
 │     This is free software; you can redistribute it and/or modify           │
 │     it under the terms of the GNU General Public License as published by   │
 │     the Free Software Foundation; either version 3 of the License, or      │
 │     (at your option) any later version.                                    │
 │     This code is distributed in the hope that it will be useful,           │
 │     but WITHOUT ANY WARRANTY; without even the implied warranty of         │
 │     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          │
 │     GNU General Public License for more details.                           │
 │                                                                            │
 │     You should have received a copy of the GNU General Public License      │
 │     along with this program.  If not, see <http://www.gnu.org/licenses/>   │
 │                                                                            │
 * ────────────────────────────────────────────────────────────────────────── */


#if defined(__STDC__)
#  if (__STDC_VERSION__ >= 199901L)
#     define _XOPEN_SOURCE 700
#  endif
#endif
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <omp.h>

#define DEFAULT 10

int main( int argc, char **argv )
{
  // If the number of arguments passed is larger than 1 count them, else use 10 as default.
  int  i = (argc > 1 ? atoi(*(argv+1)) : DEFAULT );
  int  nthreads;
  int *array;

 #pragma omp parallel
 #pragma omp master
  nthreads = omp_get_num_threads();

  //allocate space for an array of integers of size nthreads
  array = (int*)calloc( nthreads, sizeof(int) );
  
  // Now we have both i and array firstprivate
 #pragma omp parallel firstprivate( i, array )
  {
    int me = omp_get_thread_num();
    
    // Here we can refer to both i and array.
    // Although they are *different* memory region
    // than the ones that are hosted in the
    // serial region, their value at the entry
    // of the parallel region is initialized
    // to the value that the corresponding variables
    // have in the serial region.

    
    array[me] = i + me;   // a perfectly valid reference
    
    // This does not make our code fail, cause the variable array still exists in the serial region
    //  and later we will be able to access it.
    array = NULL;         // we screw up.. but only in
                          // this scope because this
                          // array is _not_ the same
                          // than that outise the p-region
  }

  for( int j = 0; j < nthreads; j++ )
    printf("entry %3d is %3d (expected was %3d)\n",
	   j, array[j], i + j );

  free(array);
  return 0;
}
