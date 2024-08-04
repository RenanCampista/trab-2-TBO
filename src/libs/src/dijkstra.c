#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#include "../libs/PQ.h"
#include "../libs/dijkstra.h"

void initialize_single_source(Graph *graph, PQ *h, long double *dist, int src) {
    int num_nodes = graph_get_num_nodes(graph);
    for (int i = 0; i < num_nodes; i++) {
        PQ_insert(h, i, i == src ? 0.0 : DBL_MAX);
        dist[i] = i == src ? 0 : DBL_MAX;
    }
}

void relax(Graph *graph, PQ *h, long double *dist, int u) {
    int num_nodes = graph_get_num_nodes(graph);
    long double u_priority = PQ_get_priority(h, u);

    for (int i = 0; i < num_nodes; i++) {
        long double w = graph_get_cost_from_edge(graph, u, i);
        if (dist[i] > u_priority + w && w != -1) {
            dist[i] = u_priority + w;
            PQ_decrease_key(h, i, u_priority + w);
        }
    }
}

long double *dijkstra_algorithm(Graph *graph, int src) {
    int num_nodes = graph_get_num_nodes(graph);
    PQ *h = PQ_init(num_nodes);
    long double *dist = calloc(num_nodes, sizeof(long double));

    initialize_single_source(graph, h, dist, src);

    while (!PQ_empty(h)) {
        int u = PQ_min(h);
        PQ_delmin(h);
        relax(graph, h, dist, u);
    }

    PQ_finish(h);
    return dist;
}