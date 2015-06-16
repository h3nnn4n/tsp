#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "queue.h"

int main(){
    srand(time(NULL));
    _queue *q;

    q = queue_init();

    int i;

    for (i=0; i<30; i++){
        queue_insert(q, rand()%10);
    }

    queue_print(q);

    for (i=0; i<10;i++){
        printf("%d\n", queue_remove(q));
    }

    return EXIT_SUCCESS;
}
