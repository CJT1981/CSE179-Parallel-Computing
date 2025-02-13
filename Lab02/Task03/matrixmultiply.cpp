#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

// Defining variables for dimensions of our two matrices
const int matrix_A_Rows = 60;
const int matrix_A_Columns = 15;
const int matrix_B_Columns = 30;

int main()
{
  int thread_id, num_of_threads, i, j, k, chunk;
  double a[matrix_A_Rows][matrix_A_Columns],
      b[matrix_A_Columns][matrix_B_Columns],
      c[matrix_A_Rows][matrix_B_Columns];
  chunk = 15;

#pragma omp parallel shared(a, b, c, num_of_threads, chunk) private(thread_id, i, j, k)
  {
    thread_id = omp_get_thread_num();
    }
}
