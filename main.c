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
    queue_insert(q, 1);
    queue_insert(q, 2);
    queue_insert(q, 5);
    queue_insert(q, 2);
    queue_insert(q, 9);
    queue_insert(q, 7);

    _queue *a = queue_init();
    queue_insert(a, 3);
    queue_insert(a, 4);
    queue_insert(a, 6);
    queue_insert(a, 10);

    q = queue_merge(q, a);
    queue_print(q);

    return EXIT_SUCCESS;
    _restricao *r;
    r = restricao_init(-1, -1);

    q = branch(r, tsp, 5, 2); 
    queue_print(q);

    for (i=3; i<n; i++){
        puts("\n--- NEW ------------------");

        _queue *q2 = branch(r, tsp, 5, i);

        q = queue_merge(q, q2);
        queue_print(q);
    }

    return EXIT_SUCCESS;
}
