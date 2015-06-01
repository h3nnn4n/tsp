#ifndef __HEAP
#define __HEAP

typedef struct __heap{
    struct __heap *last;
    struct __heap *left;
    struct __heap *right;
    struct __heap *top;

    void *data;

    int levels;
    int free_pos;
    int nitens;
    int nitens_max;
} _heap;

_heap *heap_init(void*);
_heap* heap_add(_heap *, _data*);
int heap_sanity(_heap*);
void heap_insert(_heap*, void*);
void heap_swap(_heap*, _heap*);
void heapify(_heap*);
void *heap_get_data(_heap*);
void heap_prealloc(_heap*, int);
void heap_prealloc1(_heap*);

#endif /* __HEAP */
