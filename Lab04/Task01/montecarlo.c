#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define NUM_THREADS 32
#define SAMPLE_POINTS_PER_THREAD 10000

int hits[NUM_THREADS];
int total_hits = 0;

void *compute_pi(void *arg)
{
  int thread_id = *(int *)arg;
  int seed = thread_id;
  int local_hits = 0;
  double x_coord, y_coord;

  for (int i=0; i<SAMPLE_POINTS_PER_THREAD; i++)
  {
    x_coord = (double)(rand_r(&seed)) / RAND_MAX - 0.5;
    y_coord = (double)(rand_r(&seed)) / RAND_MAX - 0.5;
    if((x_coord * x_coord + y_coord * y_coord) < 0.25)
      local_hits++;
  }
  hits[thread_id] = local_hits;  // Store result in shared array
  pthread_exit(0);
}

int main(int argc, char *argv[]) {
  pthread_t p_threads[NUM_THREADS];
  pthread_attr_t attr;
  int num_threads = 4;  // Default thread count

  printf("Enter the number of threads (4, 8, 16, or 32): ");
  scanf("%d", &num_threads);
  
  if (num_threads != 4 && num_threads != 8 && num_threads != 16 && num_threads != 32) {
      printf("Invalid number of threads. Using default (4).\n");
      num_threads = 4;
  }  

  clock_t start_time = clock();  // Start measuring time

  pthread_attr_init(&attr);
  int thread_ids[NUM_THREADS];

  for (int i = 0; i < num_threads; i++) {
      thread_ids[i] = i;
      pthread_create(&p_threads[i], &attr, compute_pi, &thread_ids[i]);
  }

  for (int i = 0; i < num_threads; i++) {
      pthread_join(p_threads[i], NULL);
      total_hits += hits[i];
  }

  double pi_estimate = 4.0 * total_hits / (num_threads * SAMPLE_POINTS_PER_THREAD);
  clock_t end_time = clock();  // End measuring time
  double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

  printf("Estimated PI = %f\n", pi_estimate);
  printf("Execution Time: %f seconds\n", elapsed_time);

  return 0;
}