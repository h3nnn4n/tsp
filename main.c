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

    q = queue_init();
    queue_insert(q, 0);
    queue_insert(q, 0);
    queue_insert(q, 0);

    _restricao *r;
    r = restricao_init(1, 4);
    restricao_insert(r, 2, 5);
    restricao_insert(r, 3, 4);

    //printf("\n%d %d %d %d\n", r->s, r->t, r->next->s, r->next->t);
    printf("%d\n", is_a_cycle(r));

    printf("\n%d \n", relax(r, tsp, n, 0));

    return EXIT_SUCCESS;
}
