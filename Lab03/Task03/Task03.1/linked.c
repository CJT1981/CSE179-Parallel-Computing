#include <stdlib.h>
#include <stdio.h>
#include "omp.h"

#ifndef N
#define N 5
#endif
#ifndef FS
#define FS 38
#endif

struct node {
    int data;
    int fibdata;
    struct node* next;
};

int fib(int n) {
    int x, y;
    
    if (n < 2) {
        return (n);
    } else {
        x = fib(n - 1);
        y = fib(n - 2);
        return (x + y);
    }
}

void processwork(struct node* p)
{
    int n;
    n = p->data;
    p->fibdata = fib(n);
}

struct node* init_list(struct node* p) {
    int i;
    struct node* head = NULL;
    struct node* temp = NULL;

    head = malloc(sizeof(struct node));
    p = head;
    p->data = FS;
    p->fibdata = 0;

    for (i=0; i< N; i++) {
        temp = malloc(sizeof(struct node));
        p->next = temp;
        p = temp;
        p->data = FS + i + 1;
        p->fibdata = i+1;
    }
    p->next = NULL;
    return head;
}

/*
  OpenMP tasks to use, #pragma omp parallel & #pragma omp single
    - #pragma omp parallel -> will create a team of threads 
    - #pragma omp -> single ensures that only one thread starts 
                     traversing the list 
*/
int main(int argc, char *argv[]) {
    double start, end;
    struct node *p=NULL;
    struct node *temp=NULL;
    struct node *head=NULL;
    printf("Process linked list\n");
    printf(" Each linked list node will be processed by function 'processwork()'\n");
    printf(" Each ll node will compute %d fibonacci numbers beginning with %d\n",N,FS);
    printf("Parallelizing linked list processing with OpenMP tasks\n");

    p = init_list(p);
    head = p;

    /*
      #pragma omp parallel -> creates a team of threads 
      #pragma omp single -> ensures only one thread initiates traversal
      #pragma omp task firstprivate(p) -> each node's work runs as a 
                                          separate task
        firstprivate(p) -> ensures each task gets a private copy of p
    */
    start = omp_get_wtime();
    #pragma omp parallel
    {
      #pragma omp single
      {
        while (p != NULL) {
          #pragma omp task firstprivate(p)
          {
            processwork(p);
          }
          p = p->next;
        }
      }
    }

    end = omp_get_wtime();
    p = head;
    while (p != NULL) {
        printf("%d : %d\n",p->data, p->fibdata);
        temp = p->next;
        free (p);
        p = temp;
    }

    free (p);
    
    printf("Compute Time: %f seconds\n", end - start);
    return 0;
}
