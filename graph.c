#include <stdio.h>
#include <stdlib.h>

#include "node.h"
#include "vector.h"
#include "edge.h"
#include "graph.h"

struct Graph {
    Vector *nodes;
};

Graph *graph_construct(int num_nodes) {
    Graph *g = calloc(1, sizeof(Graph));
    if (g == NULL)
        exit(printf("Error: graph_construct failed to allocate memory.\n"));
        
    g->nodes = vector_construct();
    for (int i = 0; i < num_nodes; i++)
        vector_push_back(g->nodes, node_construct());

    return g;
}

void graph_destruct(Graph *graph) {
    for (int i = 0; i < vector_size(graph->nodes); i++) 
        node_destruct((Node *) vector_get(graph->nodes, i));
    vector_destruct(graph->nodes);
    free(graph);
}

void graph_add_node(Graph *graph, int src, int neighbor, double cost){
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

Graph* graph_read(char* file_name) {
    FILE *file = fopen(file_name, "r");
    if (file == NULL)
        exit(printf("Error: graph_read failed to open file.\n"));
    
    int num_nodes, num_edges;
    fscanf(file, "\n%d %d", &num_nodes, &num_edges);
    
    int num_servers, num_clients, num_monitors;
    fscanf(file, "\n%d %d %d", &num_servers, &num_clients, &num_monitors);

    int *servers = (int *) calloc(num_servers, sizeof(int));
    int *clients = (int *) calloc(num_clients, sizeof(int));
    int *monitors = (int *) calloc(num_monitors, sizeof(int));
    if (servers == NULL || clients == NULL || monitors == NULL)
        exit(printf("Error: graph_read failed to allocate memory.\n"));

    for (int i = 0; i < num_servers; i++) 
        fscanf(file, "\n%d", &servers[i]);
    for (int i = 0; i < num_clients; i++) 
        fscanf(file, "\n%d", &clients[i]);
    for (int i = 0; i < num_monitors; i++) 
        fscanf(file, "\n%d", &monitors[i]);

    Graph *graph = graph_construct(num_nodes);

    for (int i = 0; i < num_edges; i++) {
        int src, neighbor;
        double cost;
        fscanf(file, "%d %d %lf", &src, &neighbor, &cost);
        graph_add_node(graph, src, neighbor, cost);
    }
    fclose(file);

    //set node types
    graph_set_node_type(
        graph, 
        servers, 
        clients, 
        monitors, 
        num_servers, 
        num_clients, 
        num_monitors
    );

    free(servers);
    free(clients);
    free(monitors);
    return graph;
}

void graph_print(Graph *graph) {
    for (int i = 0; i < vector_size(graph->nodes); i++) {
        printf("Node %d\n", i);
        node_print((Node *) vector_get(graph->nodes, i));
    }
}