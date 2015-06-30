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

//void queue_insert(_queue *q, int n){
_queue_n *queue_insert(_queue *q, int n, _restricao *res, int atual){
    _queue_n *node = (_queue_n*) malloc (sizeof(_queue_n));

    if (node == NULL){
        fprintf(stderr,"Malloc problems!\n");
        exit(1);
    }

    node->n = n;

    node->limite    = -1;
    node->atual     = atual;
    node->next      = NULL;
    node->restricao = res;

    // Se a fila estiver vazia
    if(q->end == NULL && q->start == NULL){
        q->end   = node;
        q->start = node;

    } else {

        // Se for menor que o primeiro elemento
        if (n < q->start->n){
            node->next = q->start;
            q->start = node;

        // Senao procura pela posicao correta
        } else {
            _queue_n *aux = q->start;

            // percorre a fila até achar a posição na qual o proximo 
            // elemento é menor que o elemento a ser inserido
            // ou anda até o final e insere na ultima posição
            if (aux->next != NULL){
                while(aux->next != NULL && node->n > aux->next->n) {
                    aux = aux->next;
                }
            }

            // Se achar uma posição antes do final
            if (aux->next !=NULL){
                node->next = aux->next;
                aux->next = node;
                
            // senao insere no final
            } else {
                aux->next = node;
                node->next = NULL;
                q->end = node;
            }
        }
    }

    q->size++;

    return node;
}

void restricao_print(_restricao *q){
    _restricao *aux = q;

    printf(" | ");

    while(aux != NULL){
        if (aux->s != -1 && aux->t != -1){
            printf("%2.d %2.d | ", aux->s, aux->t);
        }
        aux = aux->next;
    }
    puts("");
}

void queue_print(_queue *q){
    _queue_n *aux = q->start;

    puts("-- QUEUE -------");
    while(aux != NULL){
        printf("%d -> ", aux->n);

        restricao_print(aux->restricao);
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

_queue_n *queue_pop(_queue *q){
    _queue_n *tmp = q->start;

    q->start = q->start->next;

    if ( q->start == NULL ){
        q->end = NULL;
    }

    _queue_n *aux = (_queue_n*) malloc (sizeof(_queue_n));

    memcpy(aux, tmp, sizeof(_queue_n));

    q->size--;
    free(tmp);
    return tmp;
}

_queue* queue_merge(_queue *a, _queue *b, int *lower_bound){
    if (a->start == NULL){
        return b;
    } else if (b->start == NULL) {
        return a;
    } else {
        _queue *q = queue_init();
        _queue_n *aux, *auxa, *auxb, *old;

        int flag = 1;
        q->size = a->size + b->size;

        auxa = a->start;
        auxb = b->start;

        while (auxa != NULL && auxb != NULL){
            if (auxa->n < auxb->n){
                if (flag) {
                    flag--;
                    q->start = auxa;
                    aux = q->start;
                } else {
                    aux->next = auxa;
                    aux = aux->next;
                }
                auxa = auxa->next;
            } else {
                if (flag) {
                    flag--;
                    q->start = auxb;
                    aux = q->start;
                } else {
                    aux->next = auxb;
                    aux = aux->next;
                }
                auxb = auxb->next;
            }
        }

        if (auxa != NULL && aux != NULL){ 
            aux->next = auxa;
            q->end = a->end;
        }

        if (auxb != NULL){
            aux->next = auxb;
            q->end = b->end;
        }

        //_queue_n *aux3 = q->start;

        //if (aux3 != NULL){

            //while (aux3->next != NULL){
                //aux3 = aux3->next;
            //}
            //q->end = aux3;
        //}

        aux = q->start;

        while (aux->next != NULL){
            if (aux->n > *lower_bound) {
                q->end = old;
            }
            old = aux;
            aux = aux->next;
        }  

        return q;
    }
}

_restricao* restricao_init(int a, int b){
    _restricao *res = (_restricao*) malloc (sizeof(_restricao));

    res->next = NULL;
    res->s = a;
    res->t = b;

    return res;
}

void restricao_insert(_restricao *res, int a, int b){
    _restricao *new = (_restricao*) malloc (sizeof(_restricao));

    _restricao *aux = res;

    while (aux->next != NULL){
        aux = aux->next;
    }

    aux->next = new;
    new->s = a;
    new->t = b;
    new->next = NULL;
}

void restricao_pop(_restricao *res){
    _restricao *aux;
    _restricao *old;

    aux = res;

    if (res == NULL){
        return;
    }

    while(aux->next != NULL){
        old = aux;
        aux = aux->next;
    }

    free(aux);
    old->next = NULL;
}

// Branches the tree
_queue* branch(_restricao *res, int **tsp, int n, int a, _queue_n *feasible){
    _queue* q = queue_init();

    // Do an working copy of the restriction list
    _restricao *bkp = restricao_copy(res);

    int i;

    for (i=1; i<=n; i++){
        // Skips an edge (i, i)
        if (i == a) {
            continue;
        }

        // Insert a new restriction
#ifdef CAN_I_HAZ_DEBUG
        /*printf("branch for | %2.d %2.d |\n", a, i);*/
#endif
        restricao_insert(bkp, a, i); 

        // Check for a cycle, if there is one remove the conflict
        // otherwise get the relaxation value
        if (is_a_cycle(bkp, n)){
#ifdef CAN_I_HAZ_DEBUG
            printf(" is a cycle\n");
            puts("\n-------");
#endif
        } else {
#ifdef CAN_I_HAZ_DEBUG
            puts("\n-------");
#endif


            int val = relax(bkp, tsp, n, a, NULL);

            _restricao *res_copy = restricao_copy(bkp);
            _queue_n* qq = queue_insert(q, val, res_copy, a);

            if (n == a) {
                //puts("Feasible solution found!");
                qq->limite = val;
                //exit(0);
            }

        }
        restricao_pop(bkp);
    }


    return q;
}

// Given a matrix of costs and a list with restrictions
// return the relaxation value
int relax(_restricao *r, int **tsp, int n, int a, _queue_n *feasible){
    int i, j;
    int min;
    int total;
    _restricao *aux;

    int *nao_usar = (int*) malloc (sizeof(int)*n);

    for (i=0;i<n;i++){
        nao_usar[i] = 0;
    }

    total = 0;

    // Prints the constraints
#ifdef CAN_I_HAZ_DEBUG
    puts("restricoes:");
    restricao_print(r);
    puts("");
#endif

    // Writes a lookup table with the constraints
    aux = r->next;
    while (aux != NULL){
        nao_usar[aux->t-1] = 1;
        aux = aux->next;
    }

    for (i=0; i<n; i++){
        aux = r;
        while (aux != NULL){
            if (aux->s == i+1){
                break;
            }
            aux = aux->next;
        }

        if (aux == NULL){
            min = 9990;
            for (j=0; j<n; j++){
                if (tsp[i][j] < min && i != j && nao_usar[j] == 0){
                    min = tsp[i][j];
                }
            }
        } else {
#ifdef CAN_I_HAZ_DEBUG
            printf("Match -> %2.d %2.d: ",aux->s, aux->t);
#endif
            min = tsp[aux->s-1][aux->t-1];
        }

#ifdef CAN_I_HAZ_DEBUG
        printf("%d \n", min);
#endif

        total += min;
    }

#ifdef CAN_I_HAZ_DEBUG
    printf("\n%d\n", total);
#endif

    return total;
}

_queue* bound(_queue *q, _queue_n *feasible, int *lower_bound){
    _queue *new = NULL; 
    _queue_n *a = q->start; 
    _queue_n *b = NULL;

    while (a != NULL){
        if (a->limite >= 0 && a->limite < (*lower_bound)) {
            *lower_bound = a->limite;
            //system("beep");
            break;
        }
        a = a->next;
    }

    if (a != NULL) {
        //puts("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
        //puts("bounding");

        new = queue_init();
        b = q->start;
        while (b != NULL) {
            if (b->n < a->limite){
                queue_insert(new, b->n, b->restricao, b->atual);
            }
            b = b->next;
        }
    }

    if (new != NULL) {
        return new;
    } else {
        return q;
    }
}

_queue_n *queue_poke(_queue *q){
    _queue_n *aux = q->start;

    return aux;
}

_restricao* restricao_copy(_restricao *r){
    _restricao *aux = r;
    _restricao *n;

    if (aux == NULL){
        fprintf(stderr,"NONONONONO");
        return NULL;
    }

    n = restricao_init(aux->s, aux->t);
    //printf("\n-----------------\n Copying | %d %d", r->s, r->t);

    //while (aux->next != NULL){
    while (aux->next != NULL){
        aux = aux->next;
        restricao_insert(n, aux->s, aux->t);
    }
    
    //puts("");

    return n;
}

int is_a_restriction(_restricao *r){
    // TODO 
    // wtf is this?
    return 1;
}

int dfs(int **g, int *visited, int s, int n){
    int i;
    //int *vis;

    //vis = (int*) malloc (sizeof(int) * n);
    //for (i=0; i<n; i++){
        //vis[i] = 0;
    //}

    for (i = 0 ; i < n ; i++){
        if (g[s][i] == 1){
            if (visited[i] == 0){
                visited[i] = 1;
                if (dfs(g, visited, i, n) == 1){
                    return 1;
                }
                //visited[i] = 0;
            } else {
                return 1;
            }
        }
    }

    return 0;
}

// Detects if there is a cycle in the restrictions (There should not be one)
int is_a_cycle(_restricao *r, int n){
    _restricao *a;
    _restricao *b;

    int i, j;
    int count;
    int first = 0;

    int *adj = (int*) malloc (sizeof(int) * n * n);

    for (i=0; i<n; i++){
        for (j=0; j<n; j++){
            adj[i*n + j] = 0;
        }
    }

    a = r;

    if (a->s == -1 && a->t == -1){
        a = a->next;
    }

    while (a != NULL){
        if (adj[(a->s - 1)*n + (a->t - 1)] == 1){
#ifdef CAN_I_HAZ_DEBUG
            printf("repeated\n");
#endif
            return 1;
        }
        adj[(a->s - 1)*n + (a->t - 1)] = 1;
        a = a->next;
    }

    for (i=0; i<n; i++){
        count = 0;
        for (j=0; j<n; j++){
            if (adj[i*n + j] == 1){
                count++;
            }
        }
        if(count>1){
#ifdef CAN_I_HAZ_DEBUG
            printf("out > 1\n");
#endif
            return 1;
        }
    }

    for (i=0; i<n; i++){
        count = 0;
        for (j=0; j<n; j++){
            if (adj[j*n + i] == 1){
                count++;
            }
        }
        if(count>1){
#ifdef CAN_I_HAZ_DEBUG
            printf("in > 1\n");
#endif
            return 1;
        }
    }

    a = r;

    if (a->s == -1 && a->t == -1){
        a = a->next;
    }

    while (a != NULL){
        if (a->next != NULL){
            b = a->next;
        } else {
            break;
        }

        //printf("%p %p %d %d %d %d\n", a, b, a->s, a->t, b->s, b->t);
        while(b != NULL){
            if (( a->s == b->s && a->t == b->t) || /* vertice igual */
                ( a->t == a->s || b->s == b->t) || /* self  loop */
                //( a->s == b->t && first>0)      || [> <]
                //( a->t == b->t )                || [> <]
                //( a->s == b->s )                || [> <]
                ( a->t == b->s && a->s == b->t)){  /* loop */

                return 1;
            }

            b = b->next;
        }
        first++;
        a = a->next;
    }

    int **g;
    int *visited;

    visited = (int*) malloc (sizeof(int) * n);

    g = (int**) malloc (sizeof(int*)*n);

    for (i=0; i<n; i++){
        visited[i] = 0;
        g[i] = (int*) malloc (sizeof(int)*n);
    }

    for (i=0 ; i<n ; i++){
        for (j=0 ; j<n ; j++){
            g[i][j] = 0;
        }
    }
    
    a = r;

    while (a != NULL) {
        if (a->s == -1 || a->s == -1) {
            a = a->next;
        }

        g[a->s - 1][a->t - 1] = 1;
        a = a->next;
    }

    int dfs_result = dfs(g, visited, 0, n);
    
    count = 0;

    for (i=0 ; i<n ; i++){
        if (visited[i] == 1) {
            count++;
        }
    }

    if (dfs_result == 1 && count < n) {
        return 1;
    }

    //printf("count = %d\tdfs_result %d\n", count, dfs_result);

    return 0;
}
