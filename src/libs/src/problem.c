#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#include "../include/network.h"
#include "../include/dijkstra.h"
#include "../include/problem.h"


typedef struct RoundTripTime RoundTripTime;
struct RoundTripTime {
    int server;
    int client;
    double inflation;
};


int round_trip_compare(const void *a, const void *b) {
    RoundTripTime *rtt_a = (RoundTripTime *)a;
    RoundTripTime *rtt_b = (RoundTripTime *)b;

    if (rtt_a->inflation < rtt_b->inflation)          return -1;
    else if (rtt_a->inflation > rtt_b->inflation)     return 1;
    else {
        // Critérios de desempate
        if (rtt_a->server < rtt_b->server)            return -1;
        else if (rtt_a->server > rtt_b->server)       return 1;
        else {
            if (rtt_a->client < rtt_b->client)        return -1;
            else if (rtt_a->client > rtt_b->client)   return 1;
            else                                      return 0;
        }
    }
}

double **calculate_distances(Network *network, int size, int network_get_node(Network *, int)) {
    double **dists = malloc(size * sizeof(double *));
    if (dists == NULL) 
        exit(printf("Error: init_distances failed to allocate memory\n"));

    Graph *graph = network_get_graph(network);
    int num_nodes = network_get_num_nodes(network);
    for (int i = 0; i < size; i++)
        dists[i] = dijkstra(graph, network_get_node(network, i), num_nodes);

    return dists;
}

RoundTripTime * start_processing_rtt
(Network *network, double **dist_servers, double **dist_clients, double **dist_monitors) {
    int num_servers = network_get_num_servers(network);
    int num_clients = network_get_num_clients(network);
    int num_monitors = network_get_num_monitors(network);
    // Por conta do qsort, é melhor usar um array 1D ao inves de rtt[num_servers][num_clients]
    RoundTripTime *rtt = malloc(num_servers * num_clients * sizeof(RoundTripTime));
    if (rtt == NULL) 
        exit(printf("Error: start_processing_rtt failed to allocate memory\n"));
    
    for (int server_idx = 0; server_idx < num_servers; server_idx++) {
        int server = network_get_server(network, server_idx);

        for (int client_idx = 0; client_idx < num_clients; client_idx++) {
            int client = network_get_client(network, client_idx);

            double rtt_server_client = dist_servers[server_idx][client]
                                        + dist_clients[client_idx][server];
            double min_rtt_monitor = DBL_MAX;
            //Descobrir o monitor que minimiza o rtt
            for (int monitor_idx = 0; monitor_idx < num_monitors; monitor_idx++) {
                int monitor = network_get_monitor(network, monitor_idx);

                double rtt_monitor_server = dist_monitors[monitor_idx][server] 
                                            + dist_servers[server_idx][monitor];
                double rtt_monitor_client = dist_monitors[monitor_idx][client] 
                                            + dist_clients[client_idx][monitor];
                double full_rtt_monitor = rtt_monitor_server + rtt_monitor_client;
                
                min_rtt_monitor = full_rtt_monitor < min_rtt_monitor ? full_rtt_monitor : min_rtt_monitor;
            }

            // Indice de uma matriz "unidimensional" -> linha * num_colunas + coluna.
            int rtt_index = server_idx * num_clients + client_idx;
            (&rtt[rtt_index])->server = server;
            (&rtt[rtt_index])->client = client;
            (&rtt[rtt_index])->inflation = rtt_server_client > 0 ? min_rtt_monitor / rtt_server_client : 0;
        }
    }
    return rtt;
}

void print_and_destroy
(Network *network, RoundTripTime *rtt,char *output_file, double **dist_servers, double **dist_clients, double **dist_monitors) {
    FILE *file = fopen(output_file, "w");
    if (file == NULL)
        exit(printf("Error: print_and_destroy failed to open file\n"));

    int num_servers = network_get_num_servers(network);
    int num_clients = network_get_num_clients(network);
    int num_monitors = network_get_num_monitors(network);

    int count_servers = 0;
    int count_clients = 0;
    int count_monitors = 0;

    for (int i = 0; i < num_servers * num_clients; i++) {
        fprintf(
            file, 
            "%d %d %.16lf\n",
            (&rtt[i])->server, 
            (&rtt[i])->client, 
            (&rtt[i])->inflation
        );

        // Tenta aproveitar o loop para liberar a memória alocada
        if (count_clients < num_clients)    free(dist_clients[count_clients++]);
        if (count_servers < num_servers)    free(dist_servers[count_servers++]);
        if (count_monitors < num_monitors)  free(dist_monitors[count_monitors++]);
    }
    fclose(file);

    // Se ainda houver memória alocada, libera
    for (int i = count_clients; i < num_clients; i++)   free(dist_clients[i]);
    for (int i = count_servers; i < num_servers; i++)   free(dist_servers[i]);
    for (int i = count_monitors; i < num_monitors; i++) free(dist_monitors[i]);

    free(dist_servers);
    free(dist_clients);
    free(dist_monitors);
    free(rtt);
}

void problem_solve(Network *network, char *output_file) {
    int num_servers = network_get_num_servers(network);
    int num_clients = network_get_num_clients(network);
    int num_monitors = network_get_num_monitors(network);
    double **dist_servers = calculate_distances(network, num_servers, network_get_server);
    double **dist_clients = calculate_distances(network, num_clients, network_get_client);
    double **dist_monitors = calculate_distances(network, num_monitors, network_get_monitor);

    RoundTripTime * rtt = start_processing_rtt(
        network, 
        dist_servers, 
        dist_clients, 
        dist_monitors
    );

    qsort(
        rtt, 
        num_servers * num_clients,
        sizeof(RoundTripTime), 
        round_trip_compare
    );

    print_and_destroy(
        network, 
        rtt, 
        output_file, 
        dist_servers, 
        dist_clients, 
        dist_monitors
    );
}
