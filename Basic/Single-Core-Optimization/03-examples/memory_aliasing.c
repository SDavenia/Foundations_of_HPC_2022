#include <stdio.h>
/*
This is just an example of memory aliasing that may occur
We can see how the two functions return different values if we have memory aliasing, i.e. both point to the same memory.

Even if we add restrict to the functions, the results are still different.
Even if we compile by passing -f no-strict-aliasing, so it appears that the compiler does not go into the secon one which is faster, 
 as we are perfroming sstrict aliasing.
*/

void voidfunc1(int*a,int*b){
    *a += *b;
    *a += *b;
}

void voidfunc2(int*a,int*b){
    *a+=2* *b;
}

int main(){
    // Both a and b point to the same memory location in both cases.
    int mem = 1;
    int* a;
    int* b;
    a = &mem;
    b = &mem;

    voidfunc1(a, b);
    printf("Function1 returns a=%d, b=%d\n", *a, *b);

    mem = 1;
    int* c;
    int* d;
    c = &mem;
    d = &mem;

    voidfunc2(c, d);
    printf("Function1 returns a=%d, b=%d\n", *c, *d);

    
}
