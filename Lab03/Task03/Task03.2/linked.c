#include <stdlib.h>
#include <stdio.h>
#include "omp.h"

#ifndef N
#define N 15
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

int main(int argc, char *argv[]) {
    double start, end;
    struct node *p=NULL;
    struct node *temp=NULL;
    struct node *head=NULL;
    printf("Process linked list\n");
    printf(" Each linked list node will be processed by function 'processwork()'\n");
    printf(" Each ll node will compute %d fibonacci numbers beginning with %d\n",N,FS);
    
    int i, num_of_nodes = 0;
    struct node **node_array;

    p = init_list(p);
    head = p;

    // printf("Getting number of nodes\n");
    while (p != NULL)
    {
      num_of_nodes++;
      // printf("Number of nodes: %d\n", num_of_nodes);
      p = p->next;
    }
    // printf("Total number of nodes %d\n", num_of_nodes); 

    node_array = (struct node**) malloc(num_of_nodes*sizeof(struct node*));

    // printf("Filling node array with node pointers\n");
    p = head;
    for(i = 0; i < num_of_nodes; i++)
    {
        node_array[i] = p;
        p = p->next;
    }
    // printf("Node array filled with node pointers!\n");

    start = omp_get_wtime();
    #pragma omp parallel for
    for(i = 0; i < num_of_nodes; i++)
    {
        // printf("Iteration #%d\n", i);
        processwork(node_array[i]);
    }
    end = omp_get_wtime();

    p = head;
    while (p != NULL) {
        printf("%d : %d\n",p->data, p->fibdata);
        temp = p->next;
        free (p);
        p = temp;
    }

    free (node_array);
    
    printf("Compute Time: %f seconds\n", end - start);
    return 0;
}
