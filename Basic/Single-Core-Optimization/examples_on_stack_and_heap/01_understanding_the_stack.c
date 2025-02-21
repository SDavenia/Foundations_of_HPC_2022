#if defined(__STDC__)
#  if (__STDC_VERSION__ >= 201112L)    // c11
#    define _XOPEN_SOURCE 700
#  elif (__STDC_VERSION__ >= 199901L)  // c99
#    define _XOPEN_SOURCE 600
#  else
#    define _XOPEN_SOURCE 500          // c90
#  endif
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#if _XOPEN_SOURCE >= 600
#  include <strings.h>
#endif

char   this_string_goes_in_initialized_global_data[] = "Hello World!\n";
double this_double_goes_in_initialized_global_data   = 3.1415926535897932;

int    function1 ( int, int, char *);
double function2 ( int, int, char *, double, double, double *, double );
  
/* 
Only done to show the following:
 - You can access the CPU registers using assembly coding (at the beginning)
 - argc seems to be residing on the stack, while the command line arguments not (very far from top of the stack)
 - After the local variables (in the main) the stack does not grow as it stays the same as already known.
 - Then notice how when function1 and function2 are called the stack RBP and RSP are moved, and the stack size is changed accordingly.
*/


int main ( int argc, char **argv )
{

  register long long int myRBP __asm__("rbp");   // this way you can directly access a CPU register
  register long long int myRSP __asm__("rsp");   // BP is the Base of the Stack and SP is the Top of the Stack
						 //
  
  printf("------------------------------\n"
	 "%s\n\n"
	 "My RBP points to %p "
	 "My RSP points to %p "
	 " ( stack size: %zd )\n",
	 __FUNCTION__, (void*)myRBP, (void*)myRSP, (void*)myRBP - (void*)myRSP ); 
	 //void* means no type, so pointer arithmetic happens by byte

  printf("\targc resides at %p [ %zd bytes-offset from RSP]\n",
	 &argc,
	 (void*)&argc - (void*)myRSP);
	 
  for ( int ii = 0; ii < argc; ii++ )
    {
      printf("\targ%d's pointer resides at %p [ %zd bytes-offset from RSP]\n"
	     "\targ%d resides at %p [ %zd bytes-offset from RSP]\n\n",
	     ii, //argc argument we are considering
	     argv + ii, //the memory address of that argument using pointer arithmetic
	     (void*)(argv+ii) - (void*)myRSP, //where it is wrt stack pointer
	     ii, *(argv+ii),
	     (void*)*(argv+ii) - (void*)myRSP);
    }

  int    add_4bytes_to_stack;
  double add_8bytes_to_stack;
  
  printf("after the local variables (*):\n"
	 "My RBP points to %p\n"
	 "My RSP points to %p\n"
	 "\n(*) the stack has not changed because the compiler\n"
	 "    already knew about these latter variales\n\n",
	 (void*)myRBP, (void*)myRSP );

  
  printf("\tadd_4bytes_to_stack resides at %p [ %zd bytes-offset from RSP]\n"
	 "\tadd_8bytes_to_stack resides at %p [ %zd bytes-offset from RSP]\n",
	 &add_4bytes_to_stack,
	 (void*)&add_4bytes_to_stack - (void*)myRSP, // distance between these two variables
	 &add_8bytes_to_stack,
	 (void*)&add_8bytes_to_stack - (void*)myRSP );
  
  // Call function 1 with args 1,2 and the string hello_world, NOT IN THE STACK.
  function1( 1, 2, this_string_goes_in_initialized_global_data);
  
  return 0;
}


int function1( int iarg1, int iarg2, char *sarg3 )
//
// n.b. just get the point.. the exact placement in registers is
//      compiler dependent
//
{

  register long long int myRBP __asm__("rbp");
  register long long int myRSP __asm__("rsp");
  register long long int myRDI __asm__("rdi");
  register long long int myRSI __asm__("rsi");
  register long long int myRDX __asm__("rdx");
  
  int    add_4bytes_to_stack;

  printf("------------------------------\n"
	 "%s\n\n"
	 "RBP points to %p, RSP points to %p (stack size: %zd)\n"
	 //"\tdata (%lu bytes long) resides at %p [ %zd bytes-offset from RSP]\n"
	 "\tadd_4bytes_to_stack resides at %p [ %zd bytes-offset from RSP]\n"	 
	 "\t RDI register value is %lld\n"
	 "\t RSI register value is %lld\n"
	 "\t RDX register value is %p ( sarg3 points to %p)\n",
	 __FUNCTION__,
	 (void*)myRBP, (void*)myRSP, (void*)myRBP - (void*)myRSP,
	 /* sizeof(data_t), &data, */
	 /* (void*)&data - (void*)myRSP, */
	 &add_4bytes_to_stack,
	 (void*)&add_4bytes_to_stack - (void*)myRSP,
	 myRDI, myRSI, (void*)myRDX, this_string_goes_in_initialized_global_data);

  //  printf("%s\n", data.tag_for_this_data );
  
  function2( 1, 2, this_string_goes_in_initialized_global_data, 1.0, 2.0, &this_double_goes_in_initialized_global_data, 3.0 );

  return 0;
}



double function2( int iarg1, int iarg2, char *sarg3, double darg1, double darg2, double *dparg1, double darg3 )
//
// n.b. just get the point.. the exact placement in registers is
//      compiler dependent
//
{
  register long long int myRBP __asm__("rbp");
  register long long int myRSP  __asm__("rsp");
  register long long int myRDI  __asm__("rdi");
  register long long int myRSI  __asm__("rsi");
  register long long int myRDX  __asm__("rdx");
  register long long int myRCX  __asm__("rdx");
  register double        myXMM0 __asm__("xmm0");
  register double        myXMM1 __asm__("xmm1");
  register double        myXMM2 __asm__("xmm2");
  
  int    add_4bytes_to_stack;
  double double_val = 0;

  printf("------------------------------\n"
	 "%s\n\n"
	 "RBP points to %p, RSP points to %p (stack size: %zd)\n"
	 "\tadd_4bytes_to_stack resides at %p [ %zd bytes-offset from RSP]\n"
	 "\tdouble_val resides at %p [ %zd bytes-offset from RSP]\n"
	 "\t RDI   register value (iarg1  ) is %lld\n"
	 "\t RSI   register value (iarg2  ) is %lld\n"
	 "\t RDX   register value (*sarg3 ) is %p ( sarg3 points to %p)\n"
	 "\t XMM0  register value (darg1  ) is %g\n"
	 "\t XMM1  register value (darg2  ) is %g\n"
	 "\t RCX   register value (*dparg1) is %p ( dparg1 points to %p)\n"
	 "\t XMM2  register value (darg3  ) is %g\n",
	 __FUNCTION__,
	 (void*)myRBP, (void*)myRSP, (void*)myRBP - (void*)myRSP,
	 &add_4bytes_to_stack, (void*)&add_4bytes_to_stack - (void*)myRSP,
	 &double_val,	       (void*)&double_val - (void*)myRSP,
	 myRDI, myRSI,
	 (void*)myRDX, this_string_goes_in_initialized_global_data,
	 myXMM0, myXMM1,
	 (void*)myRCX, dparg1,
	 myXMM2 );
  
  return 0.0;
}

