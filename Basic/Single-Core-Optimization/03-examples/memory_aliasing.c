#include <stdio.h>


void voidfunc1(int*a,int*b){
    *a += *b;
    *a+=*b;
}

void voidfunc2(int*a,int*b){
    *a+=2* *b;
}

int main(){
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
