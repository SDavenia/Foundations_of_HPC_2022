#include<stdlib.h>
#include<stdio.h>
#include<string.h>

/*
This is just to see how arrays of struct work.
*/

typedef struct
{
  char    char_field;
  double  double_field;
  int     int_field;
  char    char_field2;
} STRUCT_A;

int main()
{
    STRUCT_A arrayA = {'a', 2, 3, 'b'};
    printf("%c\n", arrayA.char_field);

    STRUCT_A arrayA2[2];
    printf("%p\n", arrayA2);      // Memory address where the array is stored (coincides with first array element).
    printf("%p\n", &arrayA2[1]);  // Memory address of second element of the array.
    
    arrayA2[0].char_field = 'c';
    printf("%c\n", arrayA2[0].char_field);    
    
}
