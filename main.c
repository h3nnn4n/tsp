#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "queue.h"

int main(){
    srand(time(NULL));
    _queue *q;

    int **tsp;
    int i, j;
    int n;
    _queue_n *feasible;

    scanf("%d", &n);

    tsp = (int**) malloc (sizeof(int*)*n);

    for (i=0; i<n; i++){
        tsp[i] = (int*) malloc (sizeof(int)*n);
    }

    for (i=0; i<n; i++){
        for (j=0; j<n; j++){
            scanf("%d", &tsp[i][j]);
        }
    }

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

    time_t t = clock(); 

    _restricao *r;
    r = restricao_init(-1, -1);

    q = branch(r, tsp, 5, 1, feasible); 

    //_queue_n *pp = queue_poke(q); 

    //pp->atual = 1;
    //printf("==> Branching %d %d\n", pp->atual, pp->n);

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

        if (q2->start == NULL) {
#ifdef CAN_I_HAZ_DEBUG
            puts("Infeasible");
#endif
            // If the queue is empty then there is no feasible solution in this path
        } else {
            q = queue_merge(q, q2);
            q = bound(q, NULL);
        }
        
#ifdef CAN_I_HAZ_DEBUG
        queue_print(q);
#endif

    }
    
    t = clock() - t;
 
    printf("%f %d\n",(double)t/CLOCKS_PER_SEC, n);

    return EXIT_SUCCESS;
}
