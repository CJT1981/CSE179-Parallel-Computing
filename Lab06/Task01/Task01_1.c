#include <mpi/mpi.h>
#include <stdio.h>

int main(int argc, char** argv)
{
  int rank, size, value; // Value is the variable to be broadcasted
  double start_time, end_time; // Variables to compute time

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (rank == 0)
  {
    value = 15;
    value *= value;
    printf("Process 0 initialized value: %d\n", value);
  }

  start_time = MPI_Wtime();
  MPI_Bcast(&value, 1, MPI_INT, 0, MPI_COMM_WORLD);
  end_time = MPI_Wtime();

  printf("Process %d received value: %d\n", rank, value);

  if (rank == 0)
  {
    printf("Execution time with %d processes: %f seconds\n", size, end_time - start_time);
  }

  MPI_Finalize();
  return 0;
}
