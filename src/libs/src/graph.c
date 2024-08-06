#include <stdio.h>
#include <stdlib.h>

#include "../libs/graph.h"


struct Graph {
    ForwardList **adjacency_list;
    int num_nodes;
};


Graph *graph_construct(int num_nodes) {
    Graph *g = malloc(sizeof(Graph));
    if (g == NULL)
        exit(printf("Error: graph_construct failed to allocate memory.\n"));
    g->num_nodes = num_nodes;
    g->adjacency_list = malloc(num_nodes * sizeof(ForwardList *));
    for (int i = 0; i < num_nodes; i++)
        g->adjacency_list[i] = forward_list_construct();
    return g;
}

void graph_destruct(Graph *graph) {
    for (int i = 0; i < graph->num_nodes; i++)
        forward_list_destruct(graph->adjacency_list[i]);
    free(graph->adjacency_list);
    free(graph);
}

int graph_get_num_nodes(Graph *graph) {
    return graph->num_nodes;
}

void graph_add_edge(Graph *graph, int src, int dest, double cost) {
    forward_list_push_front(graph->adjacency_list[src], src, dest, cost);
}

void graph_read(Graph *graph, FILE *file, int num_edges) {
    for (int i = 0; i < num_edges; i++) {
        int src, dest;
        double cost;
        fscanf(file, "%d %d %lf", &src, &dest, &cost);
        graph_add_edge(graph, src, dest, cost);
    }
}

ForwardList *graph_get_edges(Graph *graph, int node) {
    return graph->adjacency_list[node];
}

// debug
// void graph_print(Graph *graph) {
//     for (int i = 0; i < graph->num_nodes; i++) {
//         printf("%d: ", i);
//         forward_list_print(graph->adjacency_list[i]);
//     }
// }
