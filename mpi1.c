Write an MPI program in c to calculate sum of randomly generated 1000 numbers
(stored in array) on a cluster
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#define ARRAY_SIZE 1000
int main(int argc, char* argv[]) {
int rank, size, i;
int array[ARRAY_SIZE];
int local_sum = 0, total_sum;
MPI_Init(&argc, &argv);
MPI_Comm_size(MPI_COMM_WORLD, &size);// Get the rank of the process
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
srand(rank + time(NULL));
for(i = 0; i < ARRAY_SIZE; i++) {
array[i] = rand() % 100;
local_sum += array[i];
}
printf("Local sum for process %d is %d\n", rank, local_sum);
MPI_Reduce(&local_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
if (rank == 0) {
printf("Total sum = %d\n", total_sum);
}
MPI_Finalize();
return 0;
}
