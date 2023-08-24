// A simple program with a deadloack inside.
// Taken and adapted from somewhere on the net 
#include <stdio.h>
#include "mpi.h"
#include <stdlib.h>
int main(int argc, char *argv[])        
{
  int len;
  if (argc > 1)
	len = atoi(argv[1]);
  else
	len = 1024;  
  int ITAG_A = 100,ITAG_B = 200; 
  int irank, i, isize, idest, isrc, istag, iretag;
  float rmsg1[len];
  float rmsg2[len];
  MPI_Status recv_status;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &irank);  
  MPI_Comm_size(MPI_COMM_WORLD, &isize);  

  printf("I am rank %d of %d \n", irank,isize );
// load an array of float numbers as message
  for (i = 1; i <= len; i++)
    {
      rmsg1[i] = 100;
      rmsg2[i] = -100;
    }
  if ( irank == 0 )
    { 
      idest  = 1;
      isrc   = 1;
      istag  = ITAG_A;
      iretag = ITAG_B;
    }
  else if ( irank == 1 )
    {
      idest  = 0;
      isrc   = 0;
      istag  = ITAG_B;
      iretag = ITAG_A;
    }

  printf("Task %d sends the message with tag %d of length %d \n", irank,istag,len*sizeof(float));
  printf("Task %d receives message with tag %d of length %d \n", irank, iretag,len*sizeof(float));
  MPI_Barrier(MPI_COMM_WORLD);

  MPI_Send(&rmsg1, len, MPI_FLOAT, idest, istag, MPI_COMM_WORLD); 
  MPI_Recv(&rmsg2, len, MPI_FLOAT, isrc, iretag, MPI_COMM_WORLD, &recv_status);
  printf("Task %d has received the message\n", irank);
  MPI_Finalize();
}
