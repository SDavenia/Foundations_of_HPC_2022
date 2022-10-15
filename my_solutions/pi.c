#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
  double x,y;
  int n;
  int m = 0;

  printf("Insert the number of desired iterations ");
  scanf("%d", &n);

  for(int i = 0; i<n; i++){
    x = (double)rand()/(double)RAND_MAX;
    y = (double)rand()/(double)RAND_MAX;

    if(x*x + y*y <= 1)
      m++;

  }
  printf("The estimate of pi is %f\n", ((double)m / (double)n) * 4);

}
