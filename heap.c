#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

#include "heap.h"
#include "data.h"

int main(){
    return EXIT_SUCCESS;
}

/*
 * Allocates a new heap, set the pointers to NULL
 * and copies the first element into the heap
 */
_heap *heap_init(void *data){
    _heap *h = (_heap*) malloc (sizeof(_heap));

    h->last = NULL;
    h->left = NULL;
    h->right = NULL;
    h->top = NULL;

    memcpy(h->data, data, sizeof(_data));

    return h;
}

/*
 * Returns 1 if the heap is sane
 * 0 otherwise
 */
int heap_sanity(_heap *h){
    int r,l;
    r = 1;
    l = 1;

    /*
     * If both left and right pointers are NULL then returns 0
     * else check if the node has the heap structure and calls recursevely
     */

    if (h->right != NULL){
        if ( ((_data*)heap_get_data(h))->n > ((_data*)heap_get_data(h->right))->n ){
            heap_sanity(h->right);
        } else {
            fprintf(stderr,"Heap not sane!\n");
        }
    } else if (h->left != NULL){
        if ( ((_data*)heap_get_data(h))->n > ((_data*)heap_get_data(h->left))->n ){
            heap_sanity(h->left);
        } else {
            fprintf(stderr,"Heap not sane!\n");
        }
    } else {
        return 1;
    }

    return r*l;
}

/*
 * Returns a void* pointer to the data in a given node
 */
void* heap_get_data(_heap* h){
    return h->data;
}
