#include <stdio.h>
#include <stdlib.h>

#include "../libs/edge.h"

struct Edge {
    int dest;
    long double cost;
};


Edge *edge_construct(int dest, long double cost) {
    Edge *edge = (Edge *) calloc(1, sizeof(Edge));
    if (edge == NULL)
        exit(printf("Error: edge_construct: could not allocate memory.\n"));
    edge->dest = dest;
    edge->cost = cost;
    return edge;
}

void edge_destruct(Edge *edge) {
    free(edge);
}

int edge_get_dest(Edge *edge) {
    return edge->dest;
}

long double edge_get_cost(Edge *edge) {
    return edge->cost;
}