#include <bits/stdc++.h>
#include <mpi.h>
using namespace std;

int main(int argc, char *argv[]) {
	int npes, myrank;
	int a[10], b[10];
	
	MPI_Init(&argc, &argv);
	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD, &npes);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	if (myrank%2) {
		for (int i = 0; i < 10; i++) 
			a[i] = i*(myrank+1);

		MPI_Send(a, 10, MPI_INT, (myrank-1), 1, MPI_COMM_WORLD);
	} else {
		MPI_Recv(b, 10, MPI_INT, (myrank+1), 1, MPI_COMM_WORLD, &status);
		for (int i = 0; i < 10; i++) 
			printf("Process %d received from %d: Value = %d\n", myrank, myrank+1, b[i]);
	}

	MPI_Finalize();
}