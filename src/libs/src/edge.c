#include <stdio.h>
#include <stdlib.h>

#include "../libs/edge.h"

struct Edge {
    int dest;
    double cost;
};

Edge *edge_construct(int dest, double cost) {
    Edge *edge = (Edge *) malloc(sizeof(Edge));

    if (edge == NULL)
        exit(printf("Error: edge_create failed to allocate memory.\n"));

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

double edge_get_cost(Edge *edge) {
    return edge->cost;
}
