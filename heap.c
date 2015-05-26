#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "data.h"
#include "heap.h"

int main(){
    return EXIT_SUCCESS;
}

/*
 * Allocates a new heap, set the pointers to NULL
 * and copies the first element into the heap
 */
_data *data_init(void *data){
    _heap *h = (_heap*) malloc (sizeof(_heap));
    h->vet   = (_data*) malloc (sizeof(_data));

    memcpy(h->data, data, sizeof(_data));

    return h;
}


