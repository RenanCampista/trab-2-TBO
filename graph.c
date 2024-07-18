#include <stdio.h>
#include <stdlib.h>

#include "node.h"
#include "vector.h"
#include "edge.h"
#include "graph.h"

struct Graph {
    Vector *nodes;
};

Graph *graph_construct() {
    Graph *g = calloc(1, sizeof(Graph));
    if (g == NULL)
        exit(printf("Error: graph_construct failed to allocate memory.\n"));
        
    g->nodes = vector_construct();

    return g;
}

void graph_destruct(Graph *graph) {
    for (int i = 0; i < vector_size(graph->nodes); i++) 
        node_destruct((Node *) vector_get(graph->nodes, i));
    vector_destruct(graph->nodes);
    free(graph);
}

void graph_add_edge(Graph *graph, int src, int neighbor, double cost){
    node_add_edge((Node *) vector_get(graph->nodes, src), neighbor, cost);
}

void graph_set_node_type(Graph *graph, int *servers, int *clients, int *monitors, int num_servers, int num_clients, int num_monitors) {
    for (int i = 0; i < num_servers; i++)
        node_set_type((Node *) vector_get(graph->nodes, servers[i]), SERVER);
    for (int i = 0; i < num_clients; i++) 
        node_set_type((Node *) vector_get(graph->nodes, clients[i]), CLIENT);
    for (int i = 0; i < num_monitors; i++)
        node_set_type((Node *) vector_get(graph->nodes, monitors[i]), MONITOR);
}

void graph_read(Graph *graph, FILE *file, int num_nodes,int num_edges) {
    for (int i = 0; i < num_nodes; i++) 
        vector_push_back(graph->nodes, node_construct());

    for (int i = 0; i < num_edges; i++) {
        int src, neighbor;
        double cost;
        fscanf(file, "\n%d %d %lf", &src, &neighbor, &cost);
        graph_add_edge(graph, src, neighbor, cost);
    }
}

void graph_print(Graph *graph) {
    for (int i = 0; i < vector_size(graph->nodes); i++) {
        printf("Node %d\n", i);
        node_print((Node *) vector_get(graph->nodes, i));
    }
}