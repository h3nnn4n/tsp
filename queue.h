#ifndef __QUEUE
#define __QUEUE

typedef struct {
	int size;
	struct __queue_n *start;
	struct __queue_n *end;
} _queue;

typedef struct __queue_n {
	struct __queue_n *next;
    int n;
    _restricao *restricao;
    _list *used, *not_used;
} _queue_n;

typedef struct __list {
    struct __list next;
    int n;
} _list;

typedef struct __restricao {
    struct __restricao *next;
    int i, j;
} _restricao;

_queue* queue_init();
void queue_insert(_queue *, int);
int queue_remove(_queue *);
void queue_print(_queue *);

int queue_is_empty(_queue *);

#endif /* __QUEUE  */
