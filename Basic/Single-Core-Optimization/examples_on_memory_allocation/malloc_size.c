#define _GNU_SOURCE
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include "benchmark.h"
#ifdef __APPLE__
#include <malloc/malloc.h>
#define USABLE_SIZE(size) malloc_size((size))
#endif
#ifdef __linux__
#include <malloc.h>
#define USABLE_SIZE(size) malloc_usable_size((size))
#endif 
 
/*
This example is to show the overhead of memory allocation.
The function malloc_usable_size returns the number of usable bytes in the block pointed to by ptr.

Inside demo
 - Allocate memory for an array of size N of uint64_t
 - Obtain using expected how much memory is allocated by the compiler (memory + overhead)
 - Time the time to access (I THINK, not really sure about it).

So at every iteration we have:
 - Increasing size of array to allocate 

We can notice that larger arrays require longer cycles to access.
However, the overhead is in percentage much smaller  for larger ones (see that in percentage the difference between allocated and reported decreases).
*/

void demo( size_t N )
{

  int repeat        = 500;
  uint64_t * values = (uint64_t *) malloc(N * sizeof(uint64_t));
    
  size_t expected = USABLE_SIZE(values);
  printf("allocated %zu, reported allocation = %zu \n", N * sizeof(uint64_t), expected);
  BEST_TIME(USABLE_SIZE(values), expected, , repeat, 1, true);
      
  free(values);
  return;  
}


int main( void )
{
  
  printf("reported usable_size for 1B allocated: %zu \n", USABLE_SIZE(malloc(1)));
  printf("reported usable_size for 4B allocated: %zu \n", USABLE_SIZE(malloc(4)));
  printf("reported usable_size for 8B allocated: %zu \n", USABLE_SIZE(malloc(8)));
  printf("reported usable_size for 16B allocated: %zu \n", USABLE_SIZE(malloc(16)));
  printf("reported usable_size for 32B allocated: %zu \n", USABLE_SIZE(malloc(32)));
  
  // 10, 100, 1000, ....
  for( size_t N = 10; N < 100000000; N *= 10 )
    demo(N);

  return 0;
}
