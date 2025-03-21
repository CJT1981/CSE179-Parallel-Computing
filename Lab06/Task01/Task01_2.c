#include <stdio.h>
#include <stdlib.h>
#include <mpi/mpi.h>

int main(int argc, char** argv)
{
  int rank, size, array_size = 128; 
  int *array = NULL, *local_array = NULL;
  int chunk_size;
  double start_time, end_time;

  // Initialize our MPI
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  // Start time
  start_time = MPI_Wtime();

  chunk_size = array_size / size; // CHUNK SIZE FOR EACH PROCESS

  // Process 0 initializes the array
  if (rank == 0)
  {
    array = (int *)malloc(array_size * sizeof(int));
    for (int index = 0; index < array_size; index++)
    {
      array[index] = index;
    }
  }

  // Allocate memory onto all processes for our local arrays 
  local_array = (int *)malloc(chunk_size * sizeof(int));

  // Using scatter for our data onto all processes
  MPI_Scatter(array, chunk_size, MPI_INT, local_array, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

  // Updating the chunk with the addition of its rank for each 
  // element in each process
  for (int index = 0; index < chunk_size; index++)
  {
    local_array[index] += rank;
  }

  // Gather our chunks onto process 0
  MPI_Gather(local_array, chunk_size, MPI_INT, array, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

  end_time = MPI_Wtime();

  // All contents from process 0 are printed out
  if(rank == 0)
  {
    printf("Updated array:\n");
    for (int index = 0; index < array_size; index++)
    {
      printf("array[%d] = %d\n", index, array[index]);
    }

    printf("Execution time = %f seconds\n", end_time - start_time);
    free(array); // free allocated memory for array
  }

  free(local_array); // free allocated for local_array

  MPI_Finalize();

  return 0;
}
