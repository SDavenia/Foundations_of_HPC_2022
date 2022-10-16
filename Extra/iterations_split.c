#include <stdio.h>
#include <mpi.h>
#include <math.h>

int main(int argc, char** argv) {
	int rank, size, numbers_per_rank;
	int my_first, my_last;
	int numbers = 10;

	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	// Calculate the number of iterations for each rank
	numbers_per_rank = floor(numbers/size);

	if(numbers%size > 0){
	 // Add 1 in case the number of ranks doesn't divide the number of numbers
	 numbers_per_rank += 1;
	}

	// Specify the first and last iteration for each rank
	my_first = numbers_per_rank * rank;
	my_last = my_first + numbers_per_rank;

	// Run only the part of the loop this rank needs
	
	for (int i = my_first; i<my_last; i++){
		if (i < numbers){
			printf("I'm rank %d and I'm printing the number %d.\n", rank, i);
		}
	}
	MPI_Finalize();
	return 0;
	
}
