#include <stdio.h>
#include <stdlib.h>

#include "../libs/PQ.h"


typedef struct {
  int id;           
  double value;    
} Item;

#define id(A)          (A.id)                           // retorna identificador do nó
#define value(A)        (A.value)                       // retorna valor do nó
#define more(A, B)      (value(A) > value(B))           // compara nós, por valor
#define exch(A, B)      { Item t = A; A = B; B = t; }   // troca dois nós

struct PQ {
    Item *priority_queue;
    int *map;
    int size;
};


Item make_item(int id, double value) {
    Item t;
    id(t) = id;
    value(t) = value;
    return t;
}

void swap(PQ *pq, int i, int j) {
    exch(pq->priority_queue[i], pq->priority_queue[j]);
    pq->map[id(pq->priority_queue[i])] = i;
    pq->map[id(pq->priority_queue[j])] = j;
}

void fix_up(PQ *pq, Item *a, int k) {
    while (k > 1 && more(a[k/2], a[k])) {
        swap(pq, k, k/2);
        k = k/2;
    }
}

void fix_down(PQ *pq, Item *a, int sz, int k){
  while (2*k <= sz) {
    int j = 2*k;

    if (j < sz && more(a[j], a[j+1]))   j++;
    if (!more(a[k], a[j]))              break;
    
    swap(pq, k, j);
    k = j;
  }
}

PQ *PQ_init(int maxN) {
    PQ *pq = calloc(1, sizeof (PQ));
    if (pq == NULL)
        exit(printf("Error: PQ_init failed to allocate memory.\n"));

    pq->priority_queue = malloc((maxN+1) * sizeof (Item));
    pq->map = malloc((maxN+1) * sizeof (int));
    if (pq->priority_queue == NULL || pq->map == NULL)
        exit(printf("Error: PQ_init failed to allocate memory.\n"));
    return pq;
}

void PQ_insert(PQ *pq, int data, double value) {
    Item i = make_item(data, value);
    pq->size++;
    pq->priority_queue[pq->size] = i;
    pq->map[id(i)] = pq->size;
    fix_up(pq, pq->priority_queue, pq->size);
}

int PQ_delmin(PQ *pq) {
    Item min = pq->priority_queue[1];
    swap(pq, 1, pq->size);
    pq->size--;
    fix_down(pq, pq->priority_queue, pq->size, 1);
    return min.id;
}

void PQ_decrease_key(PQ *pq, int id, double value) {
    int i = pq->map[id];
    value(pq->priority_queue[i]) = value;
    fix_up(pq, pq->priority_queue, i);
}

int PQ_empty(PQ *pq) {
    return pq->size == 0;
}

void PQ_finish(PQ *pq) {
    free(pq->priority_queue);
    free(pq->map);
    free(pq);
}
