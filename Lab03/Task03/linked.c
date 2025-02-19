#include <stdlib.h>
#include <stdio.h>
#include "omp.h"

#ifndef N
#define N 5
#endif
#ifndef FS
#define FS 38
#endif
/*
  Every node will contain:
    data -> int variable 
    fibdata -> int variable that stores the computed fibonacci value
    next -> pointer to the next node in the list
*/
struct node {
    int data;
    int fibdata;
    struct node* next;
};

// Recursive Fibonaci Function
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

/*
  Function's instructions/process:
    1. Process Work retrieves node p's data value and store in variable n
    2. Compute p's fibdata value by calling fib() with n as its argument
*/
void processwork(struct node* p)
{
    int n;
    n = p->data;
    p->fibdata = fib(n);
}

/*
  init_list() process:
    1. Initialize a linked list with N nodes, N = 5
    2. The first node contains FS, FS = 38
      2a. The subsequent nodes contain (FS + i + 1), i is for-loop iteration
    3. Each node's fibdata is initialized with (i + 1)
*/
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
  1. Prints information about the program
  2. Calls init_;ist() to create and initalize the linked list 
  3. Measures execution time using omp_get_wtime()
  4. Calls processwork() sequentially on each node
  5. Prints computed values and frees memory
*/
int main(int argc, char *argv[]) {
    double start, end;
    struct node *p=NULL;
    struct node *temp=NULL;
    struct node *head=NULL;
    printf("Process linked list\n");
    printf(" Each linked list node will be processed by function 'processwork()'\n");
    printf(" Each ll node will compute %d fibonacci numbers beginning with %d\n",N,FS);
    
    p = init_list(p);
    head = p;

    start = omp_get_wtime();
    {
        while (p != NULL) {
        processwork(p);
        p = p->next;
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
