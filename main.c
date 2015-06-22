#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "queue.h"
//#include "queue.c"

int main(){
    srand(time(NULL));
    _queue *q;

    int **tsp;
    int i, j;
    int n;

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

    for (i=0; i<n; i++){
        for (j=0; j<n; j++){
            printf("%2.d ", tsp[i][j]);
        }
        puts("");
    }

    _restricao *r;
    //r = restricao_init(1, 3);
    r = restricao_init(-1, -1);

    q = branch(r, tsp, 5, 1); 

    _queue_n *pp = queue_poke(q); 
    pp->atual = 1;
    printf("==> Branching %d %d\n", pp->atual, pp->n);

    queue_print(q);

    printf("========= = = =  =  %d %d\n", q->size, queue_is_empty(q));

    while(queue_is_empty(q) == 0){
        puts("\n--- NEW ------------------------------------------------------------------------");

        int size = q->size;
        int size2 = -1;

        //printf("XXXXx %d ----\n", q->size);
        //if (queue_is_empty(q) != 0) {
        _queue_n *pp = queue_poke(q); 

        printf("==> Branching for %d with %d\n", pp->atual+1, pp->n);

        _queue *q2 = branch((queue_poke(q))->restricao, tsp, n, (queue_poke(q))->atual+1);

        if (q2->start == NULL) {
            //puts("Imminent beating to a pulp");
            queue_remove(q);
        } else {
            queue_remove(q);
            q = queue_merge(q, q2);
            size2 = q2->size;
            //printf("XXXXx %d %d %d ----\n", q->size, size2, size);
        }
        
        queue_print(q);
    }

    return EXIT_SUCCESS;
}
