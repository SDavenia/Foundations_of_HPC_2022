#include <stdio.h>
#include <omp.h>

int main()
{
    #pragma omp parallel for num_threads(2)
    for(int i=0; i< 5; i++) {
        for (int j=0; j<5; j++) {
            printf("i = %d, j= %d, threadId = %d \n", i, j, omp_get_thread_num());
        }
    }

    printf("Now with collapse(2)");

    #pragma omp parallel for num_threads(2) collapse(2)
    for(int i=0; i< 5; i++) {
        for (int j=0; j< 5; j++) {
            printf("i = %d, j= %d, threadId = %d \n", i, j, omp_get_thread_num());
        }
    }
}