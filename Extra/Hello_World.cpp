#include <iostream>
#include <mpi.h>

int main(int argc, char** argv){
	int rank, size;

	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	std::cout<<"Hello World, I am process "<<rank<<" out of "<<size<<std::endl;

	MPI_Finalize();
	return 0;
}
