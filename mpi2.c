Write an MPI program to calculate sum and average of randomly generated 1000
numbers (stored in array) on a cluster
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#define ARRAY_SIZE 1000
int main(int argc, char* argv[]) {
int rank, size, i;
int array[ARRAY_SIZE];
int local_sum = 0, total_sum;
float average;
// Initialize the MPI environment
MPI_Init(&argc, &argv);
// Get the number of processes
MPI_Comm_size(MPI_COMM_WORLD, &size);
// Get the rank of the process
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
// Seed the random number generator to get different results each time
srand(rank + time(NULL));
// Generate random numbers in each process
for(i = 0; i < ARRAY_SIZE; i++) {
array[i] = rand() % 100;
local_sum += array[i];
}
// Print the local sum of each process
printf("Local sum for process %d is %d\n", rank, local_sum);// Reduce all of the local sums into the total sum
MPI_Reduce(&local_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
// Calculate the average
average = total_sum / (float)(ARRAY_SIZE * size);
// Print the total sum and average once at the root
if (rank == 0) {
printf("Total sum = %d\n", total_sum);
printf("Average = %.2f\n", average);
}
// Finalize the MPI environment
MPI_Finalize();
return 0;
}
