#include <iostream>
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
  chunk = 4;

#pragma omp parallel shared(a, b, c, num_of_threads, chunk) private(thread_id, i, j, k)
  {
    thread_id = omp_get_thread_num();
    if (thread_id == 0) // <-- master thread
    {
      // Get number of threads based on export line in terminal
      num_of_threads = omp_get_num_threads();
      cout << "Starting Matrix Multiplication, with " << num_of_threads << " threads\n";
    }
    // Initializing matrices
    #pragma omp for schedule(static, chunk)
    for (i = 0; i < matrix_A_Rows; i++)
    {
      for (j = 0; j < matrix_A_Columns; j++)
      {
        a[i][j] = i + j;
      } 
    }

    #pragma omp for schedule(static, chunk)
    for (i = 0; i < matrix_A_Columns; i++)
    {
      for (j = 0; j < matrix_B_Columns; j++)
      {
        b[i][j] = i * j;
      }
    }
      
    #pragma omp for schedule(static, chunk) 
    for (i = 0; i < matrix_A_Rows; i++)
    {
      for (j = 0; j < matrix_B_Columns; j++)
      {
        c[i][j] = 0;
      }
    }

    #pragma omp critical
    cout << "Thread " << thread_id << " starting matrix multiply:\n";
    
    #pragma omp for schedule(static, chunk)
      for (i = 0; i < matrix_A_Rows; i++)
      {
        #pragma omp critical
        cout << "Thread: " << thread_id << " completed row " << i << endl;

        for (j = 0; j < matrix_B_Columns; j++)
          for (k = 0; k < matrix_A_Columns; k++)
            c[i][j] += a[i][k] * b[k][j];
      }
  } // end of parallel work

  cout << a << endl;
}
