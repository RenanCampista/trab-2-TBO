#include <stdio.h>
#include <stdlib.h>

#include "../libs/PQ.h"

struct PQ {
    Item *pq;
    int *map;
    int n;
    int size;
};

static void swap(PQ *pq, int i, int j) {
    exch(pq->pq[i], pq->pq[j]);
    pq->map[id(pq->pq[i])] = i;
    pq->map[id(pq->pq[j])] = j;
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
    if (j < sz && more(a[j], a[j+1])){
      j++;
    }
    if (!more(a[k], a[j])) {
      break;
    }
    swap(pq, k, j);
    k = j;
  }
}

PQ *PQ_init(int maxN) {
    PQ *pq = malloc(sizeof (PQ));
    pq->pq = malloc((maxN+1) * sizeof (Item));
    pq->map = malloc((maxN+1) * sizeof (int));
    pq->n = 0;
    pq->size = maxN;

    return pq;
}

void PQ_insert(PQ *pq, int data, double priority) {
    Item i = {data, priority};

    pq->n++;
    pq->pq[pq->n] = i;
    pq->map[id(i)] = pq->n;
    fix_up(pq, pq->pq, pq->n);
}

int PQ_delmin(PQ *pq) {
    Item min = pq->pq[1];
    swap(pq, 1, pq->n);
    pq->n--;
    fix_down(pq, pq->pq, pq->n, 1);
    return min.id;
}

int PQ_min(PQ *pq) {
    return pq->pq[1].id;
}

double PQ_get_priority(PQ *pq, int id) {
    return pq->pq[pq->map[id]].value;
}

void PQ_decrease_key(PQ *pq, int id, double value) {
    int i = pq->map[id];
    value(pq->pq[i]) = value;
    fix_up(pq, pq->pq, i);
}

bool PQ_empty(PQ *pq) {
    return pq->n == 0;
}

int  PQ_size(PQ *pq) {
    return pq->n;
}

void PQ_finish(PQ *pq) {
    free(pq->pq);
    free(pq->map);
    free(pq);
}
