#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

int main(){
    _restricao *r = restricao_init(-1, -1);

    int i;

    for(i=0; i<100; i++){
        restricao_insert(r, rand()%100, rand()%100);
    }

    for(i=0; i<200; i++){
        if(rand()%55 < 54)
            restricao_pop(r);
        else
            restricao_insert(r, rand()%100, rand()%100);
    }

    restricao_print(r);

    _restricao *q = r;

    r = restricao_init(-1, -1);

    for(i=0; i<100; i++){
        restricao_insert(r, rand()%100, rand()%100);
    }

    for(i=0; i<200; i++){
        if(rand()%55 < 54)
            restricao_pop(r);
        else
            restricao_insert(r, rand()%100, rand()%100);
    }

    restricao_print(r);

    return EXIT_SUCCESS;
}
