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

    _restricao *r;
    r = restricao_init(1, 3);
    restricao_insert(r, 2, 5);

    //printf("\n%d %d %d %d\n", r->s, r->t, r->next->s, r->next->t);
    //printf("%d\n", is_a_cycle(r));

    //printf("\n%d \n", relax(r, tsp, n, 0));

    q = branch(r, tsp, 5, 3); 

    puts("-------");
    queue_print(q);

    return EXIT_SUCCESS;
}
