#include <mpi/mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  MPI_Init(&argc, &argv);

  int size, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  // Creating the 2D Cartesian topology
  int num_of_dims = 2;
  int matrix_dims[2] = {4, 4};
  int periodic[2] = {1, 1}; // Periodic in both dimensions
  int reorder = 1;

  MPI_Comm cartesian_comm;
  MPI_Cart_create(MPI_COMM_WORLD, num_of_dims, matrix_dims, periodic, reorder, &cartesian_comm);

  // Get the local rank in the Cartesian communicator
  int local_rank;
  MPI_Comm_rank(cartesian_comm, &local_rank);

  // Comparing our local rank with the global rank of MPI_COMM_WORLD
  if (local_rank == rank)
  {
    printf("Process %d: Local rank and global rank are the same. \n", rank);
  } else 
  {
    printf("Process %d: Local rank (%d) and global rank (%d) are different.\n", rank, local_rank, rank);
  }
  
  int coordinates[2];
  MPI_Cart_coords(cartesian_comm, local_rank, num_of_dims, coordinates);

  int n_rank, s_rank, w_rank, e_rank;
  MPI_Cart_shift(cartesian_comm, 0, 1, &n_rank, &s_rank);
  MPI_Cart_shift(cartesian_comm, 1, 1, &w_rank, &e_rank);

  int neighbor_ranks[4];
  MPI_Sendrecv_replace(&local_rank, 1, MPI_INT, n_rank, 0, s_rank, 0, cartesian_comm, MPI_STATUS_IGNORE);
  neighbor_ranks[0] = local_rank;

  MPI_Sendrecv_replace(&local_rank, 1, MPI_INT, e_rank, 0, w_rank, 0, cartesian_comm, MPI_STATUS_IGNORE);
  neighbor_ranks[1] = local_rank;

  neighbor_ranks[2] = n_rank;
  neighbor_ranks[3] = w_rank;

  float average = (local_rank + neighbor_ranks[0] + neighbor_ranks[1] + neighbor_ranks[2] + neighbor_ranks[3]) / 5.0;

  printf("Process %d: Average with neighbors is %.2f.\n", rank, average);
  
  MPI_Finalize();
  return 0;
}
