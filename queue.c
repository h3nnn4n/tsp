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
