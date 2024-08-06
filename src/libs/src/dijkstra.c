#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#include "../libs/PQ.h"
#include "../libs/dijkstra.h"
#include "../libs/forward_list.h"
#include "../libs/graph.h"


void initialize_single_source(PQ *pq, double *dist, int src, int num_nodes) {
    for (int node = 0; node < num_nodes; node++) {
        dist[node] = DBL_MAX; 
        PQ_insert(pq, node, DBL_MAX);
    }
    dist[src] = 0;
    PQ_decrease_key(pq, src, 0);
}

void relax(Graph *graph, PQ *pq, double *dist, int current_node) {
    double current_priority = dist[current_node];

    ForwardList *edges = graph_get_edges(graph, current_node);
    if (edges == NULL) return;

    ForwardListIterator *it = iterator_init(edges);
    if (it == NULL) return;

    while (iterator_has_next(it)) {
        Node *node = iterator_next(it);
        if (node == NULL) continue;

        int dest_node = node_get_dest(node);
        double edge_cost = node_get_cost(node);
        if (dist[dest_node] > current_priority + edge_cost) {
            dist[dest_node] = current_priority + edge_cost;
            PQ_decrease_key(pq, dest_node, current_priority + edge_cost);
        }
    }
    iterator_finish(it);
}

double *dijkstra_algorithm(Graph *graph, int src) {
    int num_nodes = graph_get_num_nodes(graph);
    PQ *pq = PQ_init(num_nodes);
    if (pq == NULL) return NULL;

    double *dist = malloc(num_nodes * sizeof(double));
    if (dist == NULL) {
        PQ_finish(pq);
        return NULL;
    }

    initialize_single_source(pq, dist, src, num_nodes);

    while (!PQ_empty(pq)) {
        int current_node = PQ_delmin(pq);
        relax(graph, pq, dist, current_node);
    }

    PQ_finish(pq);
    return dist;
}
