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
//void restricao_init(_queue *q, int a, int b){
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

_queue* branch(_restricao *res, int **tsp, int n, int a){
    _queue* q = queue_init();

    return q;
}

int relax(_restricao *r, int **tsp, int n, int a){
    int i, j;
    int min;
    int total;
    _restricao *aux;

    total = 0;

    for (i=0; i<n; i++){

        aux = r;

        while (aux != NULL){
            if (aux->s == i){
                break;
            }

            aux = aux->next;
            printf("%p %p \n", aux, aux->next);
        }

        if (aux == NULL){
            min = 9990;
            for (j=0; j<n; j++){
                if (tsp[i][j] < min && i != j){
                    min = tsp[i][j];
                }
            }
        } else {
            min = tsp[aux->s][aux->t];
        }

        total += min;
    }

    return total;
}

int is_a_restriction(_restricao *r){

    return 1;
}

int is_a_cycle(_restricao *r){
    _restricao *a;
    _restricao *b;

    a = r;

    while (a != NULL){
        b = a->next;
        while(b != NULL){
            //printf("->  %d %d %d %d\n",a->s, a->t, b->s, b->t);

            // tests 4 cases in which the branching is illegal for the tsp

            if ((a->s == b->s && a->t == b->t) ||
                (a->t == a->s || b->s == b->t) ||
                (a->s == b->t || a->t == b->t) ||
                (a->t == b->t && a->s == b->s)){

                return 1;
            }

            b = b->next;
        }
        a = a->next;
    }

    return 0;
}
