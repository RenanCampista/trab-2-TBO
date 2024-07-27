#include <stdio.h>
#include <stdlib.h>

#include "../libs/graph.h"
#include "../libs/adjacency_matrix.h"

struct Graph {
    AdjacencyMatrix *am;
};

Graph *graph_construct(int num_nodes) {
    Graph *g = calloc(1, sizeof(Graph));
    if (g == NULL)
        exit(printf("Error: graph_construct failed to allocate memory.\n"));
    g->am = adjacency_matrix_construct(num_nodes);
    return g;
}

void graph_destruct(Graph *graph) {
    adjacency_matrix_destruct(graph->am);
    free(graph);
}

int graph_get_num_nodes(Graph *graph) {
    return adjacency_matrix_get_num_nodes(graph->am);
}

double graph_get_cost_from_edge(Graph *graph, int src, int dest) {
    return adjacency_matrix_get_cost(graph->am, src, dest);
}

void graph_add_edge(Graph *graph, int src, int dest, double cost) {
    adjacency_matrix_set_cost(graph->am, src, dest, cost);
}

void graph_read(Graph *graph, FILE *file, int num_edges) {
    for (int i = 0; i < num_edges; i++) {
        int src, dest;
        double cost;
        fscanf(file, "\n%d %d %lf", &src, &dest, &cost);
        graph_add_edge(graph, src, dest, cost);
    }
}