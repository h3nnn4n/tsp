#ifndef __QUEUE
#define __QUEUE

typedef struct __list {
    struct __list *next;
    int n;
} _list;

typedef struct __restricao {
    struct __restricao *next;
    int s, t;
} _restricao;

typedef struct {
	int size;
	struct __queue_n *start;
	struct __queue_n *end;
} _queue;

typedef struct __queue_n {
	struct __queue_n *next;
    int n;
    int limite;
    int atual;
    _restricao *restricao;
} _queue_n;

_queue_n *queue_poke(_queue *q);
_queue_n *queue_pop(_queue *q);
_queue_n *queue_insert(_queue *, int, _restricao*, int);
_queue*   queue_init();
_queue*   queue_merge(_queue *a, _queue *b, int *lower_bound);
//void    queue_insert(_queue *, int);
void      queue_print(_queue *);
int       queue_remove(_queue *);
int       queue_is_empty(_queue *);

_restricao* restricao_init(int, int);
_restricao* restricao_copy(_restricao *r);
void        restricao_insert(_restricao *, int, int);
void        restricao_pop(_restricao *);
void        restricao_print(_restricao *q);

int     is_a_cycle(_restricao *r, int n);
int     relax(_restricao *r, int **tsp, int n, int a, _queue_n *feasible);
_queue* branch(_restricao *res, int **tsp, int n, int a, _queue_n *feasible);
_queue* bound(_queue *q, _queue_n *feasible, int *lower_bound);

#endif /* __QUEUE  */
