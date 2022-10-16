#include <iostream>
#include <mpi.h>
#include <cmath>

int main(int argc, char** argv){
	int rank, size, numbers_per_rank;
	int my_first, my_last;
	int numbers = 10;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);	
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	numbers_per_rank = numbers/size;
	if (numbers%size > 0)
		numbers_per_rank += 1;

	// Now we allocate the loop indices to each core
	my_first = rank * numbers_per_rank;
	my_last = my_first + numbers_per_rank;

	for (int i = my_first; i < my_last; i++){
		if (i < numbers)
			std::cout<<"I'm rank "<<rank<<" and I'm printing number "<<i<<std::endl;
	}

	MPI_Finalize();
	return 0;
	

}
