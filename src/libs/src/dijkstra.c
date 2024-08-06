#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#include "../libs/PQ.h"
#include "../libs/dijkstra.h"
#include "../libs/forward_list.h"


void initialize_single_source(PQ *pq, double *dist, int src, int num_nodes) {
    for (int i = 0; i < num_nodes; i++) {
        dist[i] = DBL_MAX; 
        PQ_insert(pq, i, DBL_MAX);
    }
    dist[src] = 0;
    PQ_decrease_key(pq, src, 0);
}

void relax(Graph *graph, PQ *pq, double *dist, int current_node) {
    double current_priority = dist[current_node];

    ForwardList *edges = graph_get_edges(graph, current_node);
    if (edges == NULL) return;

    ForwardListIterator *it = iterator_init(edges);
    while (iterator_has_next(it)) {
        Edge *edge = iterator_next(it);
        if (edge == NULL) continue;

        int dest_edge = edge_get_dest(edge);
        double edge_cost = edge_get_cost(edge);
        if (dist[dest_edge] > current_priority + edge_cost) {
            dist[dest_edge] = current_priority + edge_cost;
            PQ_decrease_key(pq, dest_edge, current_priority + edge_cost);
        }
    }
    iterator_finish(it);
}

double *dijkstra_algorithm(Graph *graph, int src) {
    int num_nodes = graph_get_num_nodes(graph);
    double *dist = malloc(num_nodes * sizeof(double));
    if (dist == NULL)
        exit(printf("Errror: dijkstra_algorithm: failed to allocate memory\n"));
    PQ *pq = PQ_init(num_nodes);

    initialize_single_source(pq, dist, src, num_nodes);
    while (!PQ_empty(pq))
        relax(graph, pq, dist, PQ_delmin(pq));

    PQ_finish(pq);
    return dist;
}
