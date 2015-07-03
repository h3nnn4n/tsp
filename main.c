#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "queue.h"

int main(){
    srand(time(NULL));
    _queue *q;
    _queue *result = NULL;

    unsigned long int nodes;

    int **tsp;
    int i, j;
    int n;
    int lower_bound;
    int max;
    _queue_n *feasible;

    scanf("%d", &n);

    tsp = (int**) malloc (sizeof(int*)*n);

    for (i=0; i<n; i++){
        tsp[i] = (int*) malloc (sizeof(int)*n);
    }

    for (i=0; i<n; i++){
        for (j=0; j<n; j++){
            scanf("%d", &tsp[i][j]);
            if (i == 0 && j == 0) {
                max = tsp[0][0];
            } else {
                if (tsp[i][j] > max) {
                    max = tsp[i][j];
                }
            }
        }
    }

    lower_bound = (max + 1) * n;

#ifdef CAN_I_HAZ_DEBUG
    for (i=0; i<n; i++){
        for (j=0; j<n; j++){
            printf("%2.d ", tsp[i][j]);
        }
        puts("");
    }

    puts("\n--- NEW ------------------------------------------------------------------------");
#endif

    feasible = NULL;
    result = queue_init();

    nodes = 0;

   /*
    *    CLOCK BEGINS TO TICK HERE
    */ 

    time_t t = clock(); 

    _restricao *r;
    r = restricao_init(-1, -1);

    q = branch(r, tsp, 5, 1, feasible); 

#ifdef CAN_I_HAZ_DEBUG
    queue_print(q);
#endif

    while(queue_is_empty(q) == 0){

#ifdef CAN_I_HAZ_DEBUG
        puts("\n--- NEW ------------------------------------------------------------------------");
#endif

        feasible = NULL;

        _queue_n *pp = queue_pop(q); 

#ifdef CAN_I_HAZ_DEBUG
        printf("==> Branching for %d with %d\n", pp->atual+1, pp->n);
#endif

        _queue *q2 = branch(pp->restricao, tsp, n, pp->atual+1, feasible);

        nodes += q2->size;

        if (q2->start == NULL) {
            
#ifdef CAN_I_HAZ_DEBUG
            puts("Infeasible");
#endif

        // If the queue is empty then there is no feasible solution in this path
        } else {
            result->start = q2->start;
            result->end = q2->end;

            q = queue_merge(q, q2, &lower_bound);
            q = bound(q, NULL, &lower_bound);
        }
        
#ifdef CAN_I_HAZ_DEBUG
        queue_print(q);
#endif

    }
    
    t = clock() - t;

   /*
    *    CLOCK STOPS TO TICK HERE
    */ 

    result->start->next = NULL;

#ifndef SILENT
    print_result(result);
#endif
 
    printf("%f %d %ld\n",(double)t/CLOCKS_PER_SEC, n, nodes);

    return EXIT_SUCCESS;
}
