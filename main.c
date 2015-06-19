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
    queue_insert(q, 3);
    queue_insert(q, 5);
    queue_insert(q, 7);
    queue_insert(q, 9);

    puts("\n----------------------");
    queue_print(q);
    puts("\n----------------------");

    _queue *a = queue_init();
    queue_insert(a, 2);
    queue_insert(a, 4);
    queue_insert(a, 6);
    queue_insert(a, 8);
    queue_insert(a, 10);

    queue_print(a);
    q = queue_merge(q, a);

    puts("\n----------------------");

    queue_print(q);
    puts("\n----------------------");

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
