#include <stdio.h>
#include <stdlib.h>

#include "../libs/forward_list.h"


struct Edge {
    int src;
    int dest;
    double cost;
    Edge *next;
};

struct ForwardList {
    Edge *head;
    int size;
};

struct ForwardListIterator {
    Edge *edge;
};


Edge *edge_construct(int src, int dest, double cost, Edge *next) {
    Edge *edge = malloc(sizeof(Edge));
    if (edge == NULL)
        exit(printf("Error: edge_construct: could not allocate memory.\n"));
    edge->src = src;
    edge->dest = dest;
    edge->cost = cost;
    edge->next = next;
    return edge;
}

void edge_destruct(Edge *edge) {
    free(edge);
}

int edge_get_src(Edge *edge) {
    return edge->src;
}

int edge_get_dest(Edge *edge) {
    return edge->dest;
}

double edge_get_cost(Edge *edge) {
    return edge->cost;
}

ForwardList *forward_list_construct() {
    ForwardList *forward_list = calloc(1, sizeof(ForwardList));
    if (forward_list == NULL)
        exit(printf("Error: forward_list_construct: could not allocate memory.\n"));
    return forward_list;
}

void forward_list_destruct(ForwardList *forward_list) {
    Edge *edge = forward_list->head;
    while (edge != NULL) {
        Edge *next = edge->next;
        edge_destruct(edge);
        edge = next;
    }
    free(forward_list);
}

void forward_list_push_front(ForwardList *forward_list, int src, int dest, double cost) {
    forward_list->head = edge_construct(src, dest, cost, forward_list->head);
    forward_list->size++;
}

ForwardListIterator *iterator_init(ForwardList *forward_list) {
    ForwardListIterator *it = malloc(sizeof(ForwardListIterator));
    if (it == NULL)
        exit(printf("Error: forward_list_iterator_init: could not allocate memory.\n"));
    it->edge = forward_list->head;
    return it;
}

void iterator_finish(ForwardListIterator *it) {
    free(it);
}

int iterator_has_next(ForwardListIterator *it) {
    return it->edge != NULL;
}

Edge *iterator_next(ForwardListIterator *it) {
    Edge *edge = it->edge;
    it->edge = it->edge->next;
    return edge;
}
