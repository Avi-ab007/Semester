#include <bits/stdc++.h>
#include <mpi.h>
#include <cstdio>
using namespace std;

int ans[100];

void CompareSplit(int n, int lelem[], int relem[], int wspace[], bool keepsmall) {
	int i, j, k;

	for (i = 0; i < n; i++) 
		wspace[i] = lelem[i];

	if (keepsmall) {
		for (i=j=k=0; k < n; k++) {
			if (j == n || (i < n and wspace[i] < relem[j]))
				lelem[k] = wspace[i++];
			else
				lelem[k] = relem[j++];
		}
	} else {
		for (i=j=k = n - 1; k >= 0; k--) {
			if (j == 0 or (i >= 0 and wspace[i] >= relem[j]))
				lelem[k] = wspace[i--];
			else
				lelem[k] = relem[j--];
		}
	}
}

int main(int argc, char *argv[]) {
	
	int n, npes, myrank, nlocal, oddrank, evenrank;
	int *lelem, *relem, *wspace;

	MPI_Init(&argc, &argv);
	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD, &npes);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	n = atoi(argv[1]);
	nlocal = n/npes;

	lelem = new int[nlocal];
	relem = new int[nlocal];
	wspace = new int[nlocal];

	srand(myrank);
	for (int i = 0; i < nlocal; i++)
		lelem[i] = rand()%100;

	sort(lelem, lelem + nlocal);
	if (!myrank%2) {
		oddrank = myrank - 1;
		evenrank = myrank + 1;
	} else {
		oddrank = myrank + 1;
		evenrank = myrank - 1;
	}

	if (oddrank == -1 or oddrank == npes) 
		oddrank = MPI_PROC_NULL;
	if (evenrank == -1 or evenrank == npes)
		evenrank = MPI_PROC_NULL;

	for (int i = 0; i < npes - 1; i++) {
		if (i%2) {
			MPI_Sendrecv(lelem, nlocal, MPI_INT, oddrank, 1, relem, nlocal, 
				MPI_INT, oddrank, 1, MPI_COMM_WORLD, &status);
		}
		else
			MPI_Sendrecv(lelem, nlocal, MPI_INT, evenrank, 1, relem, nlocal, 
				MPI_INT, evenrank, 1, MPI_COMM_WORLD, &status);

		// printf("Process %d:\n", myrank);
		// for (int i = 0; i < nlocal; i++)
		// 	printf("%d ", lelem[i]);
		// printf("\n");
		CompareSplit(nlocal, lelem, relem, wspace, myrank < status.MPI_SOURCE);
	}
	MPI_Gather(lelem, nlocal, MPI_INT, ans, nlocal, MPI_INT,0, MPI_COMM_WORLD);
	if (myrank == 0){
		printf("print\n");
		for (int i = 0; i < n;i++)
			printf("%d: %d\n",i, ans[i]);
		printf("\n");
	}
	MPI_Finalize();
	return 0;
}