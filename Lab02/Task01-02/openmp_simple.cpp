#include <iostream>
#include "omp.h"

int main()
{
  int num_of_threads, thread_id;

#pragma omp parallel private(thread_id) // tid = thread identifier
  {
    thread_id = omp_get_thread_num();
    std::cout << "Hello World from thread: " << thread_id << std::endl;

    if (thread_id == 0) // <--- thread master
    {
      num_of_threads = omp_get_num_threads();
      std::cout << "Number of threads = " << num_of_threads << std::endl;
    }
  }

  return 0;
}