#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

int queue_is_empty(_queue *q){
    if ( q->size == 0 )
        return 1;
    return 0;
}

_queue* queue_init(){
    _queue *head = (_queue*) malloc (sizeof(_queue));
    head->size = 0;
    head->end = NULL;
    head->start = NULL;
    return head;
}

void queue_insert(_queue *q, int n){
    _queue_n *node = (_queue_n*) malloc (sizeof(_queue_n));

    node->n = n;

    if(q->end == NULL && q->start == NULL){
        q->end = node;
        q->start = node;
    } else {
        if (n <= q->start->n){
            node ->next = q->start;
            q->start = node;
        } else {
            _queue_n *aux = q->start;

            if (aux->next != NULL){
                while(node->n >= aux->next->n){
                    aux = aux->next;

                    if (aux->next == NULL){
                        break;
                    }
                }
            }

            if (aux->next !=NULL){
                node->next = aux->next;
                aux->next = node;
            } else {
                aux->next = node;
                node->next = NULL;
                q->end = node;
            }
        }
    }

    q->size++;
}

void restricao_print(_restricao *q){
    _restricao *aux = q;

    while(aux != NULL){
        printf("%d %d\n", aux->s, aux->t);
        aux = aux->next;
    }
}

void queue_print(_queue *q){
    _queue_n *aux = q->start;

    while(aux != NULL){
        printf("%d %p %p\n", aux->n, aux, aux->next);
        aux = aux->next;
    }
}

int queue_remove(_queue *q){
    _queue_n *tmp = q->start;
    int n;
    n = q->start->n;

    q->start = q->start->next;

    if ( q->start == NULL ){
        q->end = NULL;
    }

    q->size--;
    free(tmp);
    return n;
}

_restricao* restricao_init(int a, int b){
    _restricao *res = (_restricao*) malloc (sizeof(_restricao));

    res->next = NULL;
    res->s = a;
    res->t = b;

    return res;
}

void restricao_insert(_restricao *res, int a, int b){
    _restricao *n = (_restricao*) malloc (sizeof(_restricao));

    _restricao *aux = res;

    while (aux->next != NULL){
        aux = aux->next;
    }

    aux->next = n;
    n->s = a;
    n->t = b;
}

void restricao_pop(_restricao *res){
    _restricao *aux;
    _restricao *old;

    aux = res;

    while(aux->next != NULL){
        old = aux;
        aux = aux->next;
    }

    free(aux);
    old->next = NULL;
}

// Branches the tree
_queue* branch(_restricao *res, int **tsp, int n, int a){
    _queue* q = queue_init();

    int i;

    for (i=1; i<=n; i++){
       restricao_insert(res, a, i); 
       if (is_a_cycle(res)){
           restricao_pop(res);
       } else {
           //puts("-------");
           //restricao_print(res);

           queue_insert(q, relax(res, tsp, n, a));
           restricao_pop(res);
       }
    }

    return q;
}

// Given a matrix of costs and a list with restrictions
// return the relaxation value
int relax(_restricao *r, int **tsp, int n, int a){
    int i, j;
    int min;
    int total;
    _restricao *aux;

    total = 0;

    puts("restricoes:");
    restricao_print(r);
    puts("");

    for (i=0; i<n; i++){

        aux = r;

        while (aux != NULL){
            if (aux->s == i+1){
                break;
            }

            //printf("%p %p %d -> %d %d\n", aux, aux->next, i, aux->s, aux->t);
            aux = aux->next;
        }

        if (aux == NULL){
            min = 9990;
            for (j=0; j<n; j++){
                if (tsp[i][j] < min && i != j){
                    min = tsp[i][j];
                }
            }
        } else {
            //printf("Match\n");
            min = tsp[aux->s-1][aux->t-1];
        }

        printf("%d ", min);

        total += min;
    }

    printf("\n%d\n", total);

    return total;
}

int is_a_restriction(_restricao *r){

    return 1;
}

// Detects if there is a cycle in the restrictions (There should not be one)
int is_a_cycle(_restricao *r){
    _restricao *a;
    _restricao *b;
    
    int first = 0;

    a = r;

    while (a != NULL){
        b = a->next;
        while(b != NULL){
            if (( a->s == b->s && a->t == b->t) || /* vertice igual */
                ( a->t == a->s || b->s == b->t) || /* self  loop */
                ( a->s == b->t && first>0)      || /* */
                ( a->t == b->t )                || /* */
                ( a->t == b->t && a->s == b->s)){  /* redundante */

                return 1;
            }

            b = b->next;
        }
        first++;
        a = a->next;
    }

    return 0;
}
