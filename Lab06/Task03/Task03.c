#include <mpi/mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define FILENAME "mpi_data.bin"
#define NUM_INTS 10  // Each process writes 10 integers

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_File file;
    int data[NUM_INTS];

    // Writing data using individual file pointers
    for (int i = 0; i < NUM_INTS; i++) {
        data[i] = rank * NUM_INTS + i;  // Assigning values (0-9 for rank 0, 10-19 for rank 1, ...)
    }

    MPI_File_open(MPI_COMM_WORLD, FILENAME, MPI_MODE_CREATE | MPI_MODE_WRONLY, MPI_INFO_NULL, &file);

    MPI_Offset offset = rank * NUM_INTS * sizeof(int);  // Calculate offset for each process
    MPI_File_seek(file, offset, MPI_SEEK_SET);
    MPI_File_write(file, data, NUM_INTS, MPI_INT, MPI_STATUS_IGNORE);

    MPI_File_close(&file);
    MPI_Barrier(MPI_COMM_WORLD);  // Ensure all processes finish writing before reading

    // Re-opening and reading data using explicit offsets
    int read_data[NUM_INTS];
    MPI_File_open(MPI_COMM_WORLD, FILENAME, MPI_MODE_RDONLY, MPI_INFO_NULL, &file);

    offset = rank * NUM_INTS * sizeof(int);  // Compute the offset again
    MPI_File_read_at(file, offset, read_data, NUM_INTS, MPI_INT, MPI_STATUS_IGNORE);

    MPI_File_close(&file);

    // Verification: Print the read data
    printf("Process %d read: ", rank);
    for (int i = 0; i < NUM_INTS; i++) {
        printf("%d ", read_data[i]);
    }
    printf("\n");

    MPI_Barrier(MPI_COMM_WORLD);  // Sync before modifying the data

    // Rewriting data in a different order
    int new_offset = ((rank + 1) % size) * NUM_INTS * sizeof(int); // Shift data by one process

    MPI_File_open(MPI_COMM_WORLD, FILENAME, MPI_MODE_WRONLY, MPI_INFO_NULL, &file);
    MPI_File_write_at(file, new_offset, read_data, NUM_INTS, MPI_INT, MPI_STATUS_IGNORE);
    MPI_File_close(&file);

    if (rank == 0) {
        printf("\nFinal data in file (use 'od -i mpi_data.bin' to check it in ASCII).\n");
    }

    MPI_Finalize();
    return 0;
}
