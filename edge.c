#include <stdio.h>
#include <stdlib.h>

#include "edge.h"

struct Edge {
    int neighbor;
    double cost;
};

Edge* edge_construct(int neighbor, double cost) {
    Edge *c = (Edge *)calloc(1, sizeof(Edge));
    if (c == NULL)
        exit(printf("Error: edge_construct failed to allocate memory.\n"));
    c->neighbor = neighbor;
    c->cost = cost;
    return c;
}

void edge_destruct(Edge *edge) {
    free(edge);
}

int edge_get_neighbor(Edge *edge) {
    return edge->neighbor;
}

double edge_get_cost(Edge *edge) {
    return edge->cost;
}

void edge_print(Edge *edge) {
    printf("Neighbor: %d, cost: %f\n", edge_get_neighbor(edge), edge_get_cost(edge));
}