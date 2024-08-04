#include <stdio.h>
#include <stdlib.h>

#include "../libs/graph.h"
#include "../libs/forward_list.h"
#include "../libs/edge.h"

struct Graph {
    ForwardList **adjacency_list;
    int num_nodes;
};

Graph *graph_construct(int num_nodes) {
    Graph *g = calloc(1, sizeof(Graph));
    if (g == NULL)
        exit(printf("Error: graph_construct failed to allocate memory.\n"));
    g->num_nodes = num_nodes;
    g->adjacency_list = calloc(num_nodes, sizeof(ForwardList *));
    for (int i = 0; i < num_nodes; i++)
        g->adjacency_list[i] = forward_list_construct();
    return g;
}

void graph_destruct(Graph *graph) {
    for (int i = 0; i < graph->num_nodes; i++) {
        forward_list_destruct(graph->adjacency_list[i], (data_type)edge_destruct);
    }
    free(graph->adjacency_list);
    free(graph);
}

int graph_get_num_nodes(Graph *graph) {
    return graph->num_nodes;
}

long double graph_get_cost_from_edge(Graph *graph, int src, int dest) {
    ForwardList *adj_list = graph->adjacency_list[src];
    ForwardListIterator it; // Declarar como objeto, não ponteiro
    forward_list_iterator_init(&it, adj_list); // Passar o endereço do objeto
    while (forward_list_iterator_has_next(&it)) {
        Edge *edge = forward_list_iterator_next(&it);
        if (edge_get_dest(edge) == dest)
            return edge_get_cost(edge);
    }
    return -1;
}

void graph_add_edge(Graph *graph, int src, int dest, long double cost) {
    forward_list_push_back(graph->adjacency_list[src], edge_construct(dest, cost));
}

void graph_read(Graph *graph, FILE *file, int num_edges) {
    for (int i = 0; i < num_edges; i++) {
        int src, dest;
        long double cost;
        fscanf(file, "\n%d %d %Lf", &src, &dest, &cost);
        graph_add_edge(graph, src, dest, cost);
    }
}