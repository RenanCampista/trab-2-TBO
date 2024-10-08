#include <stdio.h>
#include <stdlib.h>

#include "../include/network.h"


struct Network {
    Graph *graph;
    int num_servers;
    int num_clients;
    int num_monitors;
    int *servers;
    int *clients;
    int *monitors;
};


Network *network_construct(int num_nodes, int num_servers, int num_clients, int num_monitors) {
    Network *network = malloc(sizeof(Network));
    if (network == NULL)
        exit(printf("Error: network_construct failed to allocate memory.\n"));

    network->graph = graph_construct(num_nodes);
    network->num_servers = num_servers;
    network->num_clients = num_clients;
    network->num_monitors = num_monitors;

    network->servers = malloc(num_servers * sizeof(int));
    network->clients = malloc(num_clients * sizeof(int));
    network->monitors = malloc(num_monitors * sizeof(int));
    
    if (
        network->servers == NULL || 
        network->clients == NULL || 
        network->monitors == NULL
    ) exit(printf("Error: network_construct failed to allocate memory.\n"));

    return network;
}

void network_destruct(Network *network) {
    graph_destruct(network->graph);
    free(network->servers);
    free(network->clients);
    free(network->monitors);
    free(network);
}

int network_get_num_nodes(Network *network) {    
    return graph_get_num_nodes(network->graph);
}

int network_get_num_servers(Network *network) {
    return network->num_servers;
}

int network_get_num_clients(Network *network) {
    return network->num_clients;
}

int network_get_num_monitors(Network *network) {
    return network->num_monitors;
}

int network_get_server(Network *network, int index) {
    return network->servers[index];
}

int network_get_client(Network *network, int index) {
    return network->clients[index];
}

int network_get_monitor(Network *network, int index) {
    return network->monitors[index];
}

Graph *network_get_graph(Network *network) {
    return network->graph;
}

Network *network_read(char *file_name) {
    FILE *file = fopen(file_name, "r");
    if (file == NULL)
        exit(printf("Error: network_read failed to open file.\n"));

    int num_nodes, num_edges;
    fscanf(file, "\n%d %d", &num_nodes, &num_edges);

    int num_servers, num_clients, num_monitors;
    fscanf(file, "\n%d %d %d", &num_servers, &num_clients, &num_monitors);

    Network *network = network_construct(num_nodes, num_servers, num_clients, num_monitors);

    for (int i = 0; i < num_servers; i++) 
        fscanf(file, "\n%d", &network->servers[i]);
    for (int i = 0; i < num_clients; i++) 
        fscanf(file, "\n%d", &network->clients[i]);
    for (int i = 0; i < num_monitors; i++) 
        fscanf(file, "\n%d", &network->monitors[i]);

    graph_read(network->graph, file, num_edges);
    fclose(file);
    return network;
}

//debug
// void network_print(Network *network) {
//     printf("Servers: ");
//     for (int i = 0; i < network->num_servers; i++)
//         printf("%d ", network->servers[i]);
//     printf("\n");

//     printf("Clients: ");
//     for (int i = 0; i < network->num_clients; i++)
//         printf("%d ", network->clients[i]);
//     printf("\n");

//     printf("Monitors: ");
//     for (int i = 0; i < network->num_monitors; i++)
//         printf("%d ", network->monitors[i]);
//     printf("\n");

//     graph_print(network->graph);
// }
