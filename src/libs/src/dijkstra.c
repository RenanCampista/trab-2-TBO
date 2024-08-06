#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#include "../libs/PQ.h"
#include "../libs/dijkstra.h"
#include "../libs/forward_list.h"
#include "../libs/graph.h"


void initialize_single_source(Graph *graph, PQ *pq, long double *dist, int src) {
    int num_nodes = graph_get_num_nodes(graph);
    for (int node = 0; node < num_nodes; node++) {
        dist[node] = DBL_MAX; 
        PQ_insert(pq, node, DBL_MAX);
    }
    dist[src] = 0;
    PQ_decrease_key(pq, src, 0);
}


void relax(Graph *graph, PQ *pq, long double *dist, int current_node) {
    long double current_priority = dist[current_node];

    ForwardList *edges = graph_get_edges(graph, current_node);
    ForwardListIterator *it = iterator_init(edges);
    while (iterator_has_next(it)) {
        Node *node = iterator_next(it);
        int dest_node = node_get_dest(node);
        long double edge_cost = node_get_cost(node);
        if (dist[dest_node] > current_priority + edge_cost) {
            dist[dest_node] = current_priority + edge_cost;
            PQ_decrease_key(pq, dest_node, current_priority + edge_cost);
        }
    }
}

long double *dijkstra_algorithm(Graph *graph, int src) {
    int num_nodes = graph_get_num_nodes(graph);
    PQ *pq = PQ_init(num_nodes);
    long double *dist = malloc(num_nodes * sizeof(long double));

    initialize_single_source(graph, pq, dist, src);

    while (!PQ_empty(pq)) {
        int current_node = PQ_delmin(pq);
        relax(graph, pq, dist, current_node);
    }

    PQ_finish(pq);
    return dist;
}
