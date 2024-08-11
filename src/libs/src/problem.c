#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#include "../libs/network.h"
#include "../libs/dijkstra.h"
#include "../libs/problem.h"


typedef struct RoundTripTime RoundTripTime;
struct RoundTripTime {
    int src;
    int dest;
    double rtt;
};


int round_trip_compare(const void *a, const void *b) {
    RoundTripTime *round_trip_time_a = (RoundTripTime *)a;
    RoundTripTime *round_trip_time_b = (RoundTripTime *)b;

    if (round_trip_time_a->rtt < round_trip_time_b->rtt)                    return -1;
    else if (round_trip_time_a->rtt > round_trip_time_b->rtt)               return 1;
    else {
        if (round_trip_time_a->src < round_trip_time_b->src)                return -1;
        else if (round_trip_time_a->src > round_trip_time_b->src)           return 1;
        else {
            // Critérios de desempate
            if (round_trip_time_a->dest < round_trip_time_b->dest)          return -1;
            else if (round_trip_time_a->dest > round_trip_time_b->dest)     return 1;
            else                                                            return 0;
        }
    }
}

void calculate_min_distances(Network *network, double **dist_servers, double **dist_clients, double **dist_monitors) {
    int num_servers = network_get_num_servers(network);
    int num_clients = network_get_num_clients(network);
    int num_monitors = network_get_num_monitors(network);
    Graph *graph = network_get_graph(network);

    // Para cada servidor, cliente e monitor, calcula as distâncias mínimas.
    for (int i = 0; i < num_servers; i++)
        dist_servers[i] = dijkstra_algorithm(
            graph, 
            network_get_server(network, i)
        );


    for (int i = 0; i < num_clients; i++)
        dist_clients[i] = dijkstra_algorithm(
            graph, 
            network_get_client(network, i)
        );


    for (int i = 0; i < num_monitors; i++)
        dist_monitors[i] = dijkstra_algorithm(
            graph, 
            network_get_monitor(network, i)
        );
}

double calculate_rtt(int node_a, int node_b, double *dists_a, double *dists_b) {
    return dists_a[node_b] + dists_b[node_a];
}

void start_processing_rtt
(Network *network, RoundTripTime *round_trip_times, double **dist_servers, double **dist_clients, double **dist_monitors) {
    int num_servers = network_get_num_servers(network);
    int num_clients = network_get_num_clients(network);
    int num_monitors = network_get_num_monitors(network);

    for (int server_idx = 0; server_idx < num_servers; server_idx++) {
        int server_id = network_get_server(network, server_idx);

        for (int client_idx = 0; client_idx < num_clients; client_idx++) {
            int client_id = network_get_client(network, client_idx);

            //RTT entre o servidor e o cliente atuais
            double direct_rtt = calculate_rtt(
                server_id, 
                client_id, 
                dist_servers[server_idx], 
                dist_clients[client_idx]
            );

            //Descobrir o monitor que minimiza o RTT
            double min_rtt_via_monitor = DBL_MAX;
            for (int monitor_idx = 0; monitor_idx < num_monitors; monitor_idx++) {
                int monitor_id = network_get_monitor(network, monitor_idx);

                //RTT via monitor (servidor -> monitor -> cliente)
                double rtt_via_monitor = calculate_rtt(
                                            server_id, 
                                            monitor_id, 
                                            dist_servers[server_idx], 
                                            dist_monitors[monitor_idx]
                                        ) 
                                        +
                                        calculate_rtt(
                                            monitor_id, 
                                            client_id, 
                                            dist_monitors[monitor_idx],
                                            dist_clients[client_idx]
                                        );

                if (rtt_via_monitor < min_rtt_via_monitor) 
                    min_rtt_via_monitor = rtt_via_monitor;
            }

            // Como o array é unidimensional, o índice é calculado como linha * num_colunas + coluna.
            int rtt_index = server_idx * num_clients + client_idx;
            (&round_trip_times[rtt_index])->src = server_id;
            (&round_trip_times[rtt_index])->dest = client_id;
            (&round_trip_times[rtt_index])->rtt = min_rtt_via_monitor / direct_rtt;
        }
    }
}

void print_and_destroy
(Network *network, RoundTripTime *round_trip_times,char *output_file, double **dist_servers, double **dist_clients, double **dist_monitors) {
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
            (&round_trip_times[i])->src, 
            (&round_trip_times[i])->dest, 
            (&round_trip_times[i])->rtt
        );

        // Tenta aproveitar o loop para liberar a memória alocada.
        if (count_clients < num_clients)    free(dist_clients[count_clients++]);
        if (count_servers < num_servers)    free(dist_servers[count_servers++]);
        if (count_monitors < num_monitors)  free(dist_monitors[count_monitors++]);
    }
    fclose(file);

    // Se ainda houver memória alocada, libera.
    for (int i = count_clients; i < num_clients; i++)   free(dist_clients[i]);
    for (int i = count_servers; i < num_servers; i++)   free(dist_servers[i]);
    for (int i = count_monitors; i < num_monitors; i++) free(dist_monitors[i]);

    free(dist_servers);
    free(dist_clients);
    free(dist_monitors);
    free(round_trip_times);
}

void problem_solve(Network *network, char *output_file) {
    int num_servers = network_get_num_servers(network);
    int num_clients = network_get_num_clients(network);
    int num_monitors = network_get_num_monitors(network);
    // Por conta do qsort, é melhor usar um array unidimensional ao inves de round_trip_times[num_servers][num_clients]
    RoundTripTime *round_trip_times = malloc(num_servers * num_clients * sizeof(RoundTripTime));
    double **dist_servers = malloc(num_servers * sizeof(double *));
    double **dist_clients = malloc(num_clients * sizeof(double *));
    double **dist_monitors = malloc(num_monitors * sizeof(double *));

    if (
        round_trip_times == NULL || 
        dist_servers == NULL || 
        dist_clients == NULL || 
        dist_monitors == NULL
    ) exit(printf("Error: problem_solve failed to allocate memory\n"));

    calculate_min_distances(
        network, 
        dist_servers, 
        dist_clients, 
        dist_monitors
    );

    start_processing_rtt(
        network, 
        round_trip_times, 
        dist_servers, 
        dist_clients, 
        dist_monitors
    );

    qsort(
        round_trip_times, 
        num_servers * num_clients,
        sizeof(RoundTripTime), 
        round_trip_compare
    );

    print_and_destroy(
        network, 
        round_trip_times, 
        output_file, 
        dist_servers, 
        dist_clients, 
        dist_monitors
    );
}
