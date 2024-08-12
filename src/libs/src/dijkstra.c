#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#include "../include/PQ.h"
#include "../include/dijkstra.h"
#include "../include/forward_list.h"


double* initialize_single_source(PQ *pq, int src, int num_nodes) {
    double *dist = (double *)malloc(num_nodes * sizeof(double));
    if (dist == NULL)
        exit(printf("Error: initialize_single_source failed to allocate memory.\n"));

    for (int i = 0; i < num_nodes; i++) 
        PQ_insert(pq, i, dist[i] = DBL_MAX);
    
    PQ_decrease_key(pq, src, dist[src] = 0);
    return dist;
}

void relax(Graph *graph, PQ *pq, double *dist, int current_node) {
    double current_cost = dist[current_node];
    ForwardList *edges = graph_get_edges(graph, current_node);
    if (edges == NULL) return;

    ForwardListIterator *it = iterator_init(edges);
    while (iterator_has_next(it)) {
        Edge *edge = iterator_next(it);
        if (edge == NULL) continue;

        int dest_edge = edge_get_dest(edge);
        double edge_cost = edge_get_cost(edge);
        // Se dist ate o destino > que dist ate o vertice atual + o custo da aresta, att a dist e pq
        if (dist[dest_edge] > current_cost + edge_cost)
            PQ_decrease_key(pq, dest_edge, dist[dest_edge] = current_cost + edge_cost);
    }
    iterator_finish(it);
}

double *dijkstra_algorithm(Graph *graph, int src, int num_nodes) {
    PQ *pq = PQ_init(num_nodes);
    double *dist = initialize_single_source(pq, src, num_nodes);
    
    while (!PQ_empty(pq))
        relax(graph, pq, dist, PQ_delmin(pq));

    PQ_finish(pq);
    return dist;
}
