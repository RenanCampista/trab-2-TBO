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

double calculate_rtt(int a, int b, double *dists_a, double *dists_b) {
    return dists_a[b] + dists_b[a];
}

void start_processing_rtt(Network *network, RoundTripTime *round_trip_times, double **dist_servers, double **dist_clients, double **dist_monitors) {
    int num_servers = network_get_num_servers(network);
    int num_clients = network_get_num_clients(network);
    int num_monitors = network_get_num_monitors(network);

    for (int i = 0; i < num_servers; i++) {
        int server = network_get_server(network, i);
        for (int j = 0; j < num_clients; j++) {
            int client = network_get_client(network, j);
            double rtt = calculate_rtt(
                server, 
                client, 
                dist_servers[i], 
                dist_clients[j]
            );

            double min_rtt_star = DBL_MAX;
            for (int k = 0; k < num_monitors; k++) {
                int monitor = network_get_monitor(network, k);
                double rtt_star = calculate_rtt(server, monitor, dist_servers[i], dist_monitors[k]) +
                                  calculate_rtt(monitor, client, dist_monitors[k], dist_clients[j]);

                if (rtt_star < min_rtt_star) 
                    min_rtt_star = rtt_star;
            }

            (&round_trip_times[i * num_clients + j])->src = network_get_server(network, i);
            (&round_trip_times[i * num_clients + j])->dest = network_get_client(network, j);
            (&round_trip_times[i * num_clients + j])->rtt = min_rtt_star / rtt;
        }
    }
}

void print_rtt(Network *network, RoundTripTime *round_trip_times,char *output_file) {
    FILE *file = fopen(output_file, "w");
    if (file == NULL)
        exit(printf("Error: print_rtt failed to open file\n"));

    int num_servers = network_get_num_servers(network);
    int num_clients = network_get_num_clients(network);

    for (int i = 0; i < num_servers * num_clients; i++)
        fprintf(
            file, 
            "%d %d %.16lf\n",
            (&round_trip_times[i])->src, 
            (&round_trip_times[i])->dest, 
            (&round_trip_times[i])->rtt
        );

    fclose(file);
}

void problem_solve(Network *network, char *output_file) {
    int num_servers = network_get_num_servers(network);
    int num_clients = network_get_num_clients(network);
    int num_monitors = network_get_num_monitors(network);
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

    print_rtt(network, round_trip_times, output_file);

    free(round_trip_times);
    for (int i = 0; i < num_servers; i++)
        free(dist_servers[i]);
    for (int i = 0; i < num_clients; i++)    
        free(dist_clients[i]);
    for (int i = 0; i < num_monitors; i++)
        free(dist_monitors[i]);
    free(dist_servers);
    free(dist_clients);
    free(dist_monitors);
}
