#include <stdio.h>
#include <stdlib.h>

#include "graph.h"
#include "edge.h"
#include "vector.h"

struct Graph {
    Vector **adjacency_list;
    int num_nodes;
};

Graph *graph_construct(int num_nodes) {
    Graph *g = calloc(1, sizeof(Graph));
    if (g == NULL)
        exit(printf("Error: graph_construct failed to allocate memory.\n"));
        
    g->adjacency_list = calloc(num_nodes, sizeof(Vector *));
    if (g->adjacency_list == NULL)
        exit(printf("Error: graph_construct failed to allocate memory.\n"));

    g->num_nodes = num_nodes;
    for (int i = 0; i < num_nodes; i++) 
        g->adjacency_list[i] = vector_construct();

    return g;
}

void graph_destruct(Graph *graph) {
    for (int i = 0; i < graph->num_nodes; i++) {
        for (int j = 0; j < vector_size(graph->adjacency_list[i]); j++)
            edge_destruct((Edge *) vector_get(graph->adjacency_list[i], j)); 
        vector_destruct(graph->adjacency_list[i]);
    }
    free(graph->adjacency_list);
    free(graph);
}

int graph_get_num_nodes(Graph *graph) {
    return graph->num_nodes;
}

double graph_get_cost_from_edge(Graph *graph, int src, int dest) {
    for (int i = 0; i < vector_size(graph->adjacency_list[src]); i++) {
        Edge *edge = (Edge *) vector_get(graph->adjacency_list[src], i);
        if (edge_get_dest(edge) == dest)
            return edge_get_cost(edge);
    }
    return -1;
}

void graph_add_edge(Graph *graph, int src, int dest, double cost) {
    if (src >= graph->num_nodes || dest >= graph->num_nodes) {
        printf("Error: graph_add_edge failed, node index out of bounds.\n");
        return;
    }

    vector_push_back(graph->adjacency_list[src], edge_construct(dest, cost));
}

void graph_read(Graph *graph, FILE *file, int num_edges) {
    for (int i = 0; i < num_edges; i++) {
        int src, dest;
        double cost;
        fscanf(file, "\n%d %d %lf", &src, &dest, &cost);
        graph_add_edge(graph, src, dest, cost);
    }
}