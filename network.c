#include <stdio.h>
#include <stdlib.h>

#include "network.h"
#include "graph.h"
#include "node.h"

struct Network {
    Graph *graph;
    int num_servers;
    int num_clients;
    int num_monitors;
};


Network *network_construct(int num_servers, int num_clients, int num_monitors) {
    Network *network = (Network *) calloc(1, sizeof(Network));
    if (network == NULL)
        exit(printf("Error: network_construct failed to allocate memory.\n"));

    network->graph = graph_construct();
    network->num_servers = num_servers;
    network->num_clients = num_clients;
    network->num_monitors = num_monitors;

    return network;
}

void network_destruct(Network *network) {
    graph_destruct(network->graph);
    free(network);
}

Network *network_read(char *file_name) {
    FILE *file = fopen(file_name, "r");
    if (file == NULL)
        exit(printf("Error: network_read failed to open file.\n"));

    int num_nodes, num_edges;
    fscanf(file, "\n%d %d", &num_nodes, &num_edges);

    int num_servers, num_clients, num_monitors;
    fscanf(file, "\n%d %d %d", &num_servers, &num_clients, &num_monitors);

    Network *network = network_construct(num_servers, num_clients, num_monitors);

    int *servers = (int *) calloc(num_servers, sizeof(int));
    int *clients = (int *) calloc(num_clients, sizeof(int));
    int *monitors = (int *) calloc(num_monitors, sizeof(int));
    if (servers == NULL || clients == NULL || monitors == NULL)
        exit(printf("Error: network_read failed to allocate memory.\n"));

    for (int i = 0; i < num_servers; i++) 
        fscanf(file, "\n%d", &servers[i]);
    for (int i = 0; i < num_clients; i++) 
        fscanf(file, "\n%d", &clients[i]);
    for (int i = 0; i < num_monitors; i++) 
        fscanf(file, "\n%d", &monitors[i]);

    graph_read(network->graph, file, num_nodes, num_edges);
    fclose(file);

    //set node types
    graph_set_node_type(
        network->graph, 
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

    return network;
}

void network_print(Network *network) {
    printf("Number of servers: %d\n", network->num_servers);
    printf("Number of clients: %d\n", network->num_clients);
    printf("Number of monitors: %d\n\n", network->num_monitors);
    graph_print(network->graph);
}