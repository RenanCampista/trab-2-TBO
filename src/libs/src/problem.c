#include <stdio.h>
#include <stdlib.h>

#include "../libs/network.h"
#include "../libs/edge.h"
#include "../libs/dijkstra.h"
#include "../libs/problem.h"
#include "../libs/round_trip_time.h"

typedef struct Problem Problem;
struct Problem {
    Network *network;
    RoundTripTime **round_trip_times;
    double **dist_servers;
    double **dist_clients;
    double **dist_monitors;
};

Problem *problem_construct(Network *network) {
    Problem *problem = (Problem *) calloc(1, sizeof(Problem));
    if (problem == NULL)
        exit(printf("Error: problem_construct failed to allocate memory.\n"));

    problem->network = network;
    problem->round_trip_times = (RoundTripTime **) calloc(network_get_num_servers(network) * network_get_num_clients(network), sizeof(RoundTripTime *));

    problem->dist_clients = (double **) calloc(network_get_num_clients(network), sizeof(double *));
    problem->dist_servers = (double **) calloc(network_get_num_servers(network), sizeof(double *));
    problem->dist_monitors = (double **) calloc(network_get_num_monitors(network), sizeof(double *));

    if (problem->round_trip_times == NULL || problem->dist_clients == NULL || problem->dist_servers == NULL || problem->dist_monitors == NULL)
        exit(printf("Error: problem_construct failed to allocate memory.\n"));

    return problem;

}

void problem_destruct(Problem *problem) {
    for (int i = 0; i < network_get_num_servers(problem->network) * network_get_num_clients(problem->network); i++)
        round_trip_time_destruct(problem->round_trip_times[i]);
    
    for (int i = 0; i < network_get_num_clients(problem->network); i++)
        free(problem->dist_clients[i]);

    for (int i = 0; i < network_get_num_servers(problem->network); i++)
        free(problem->dist_servers[i]);

    for (int i = 0; i < network_get_num_monitors(problem->network); i++)
        free(problem->dist_monitors[i]);

    free(problem->round_trip_times);
    free(problem->dist_clients);
    free(problem->dist_servers);
    free(problem->dist_monitors);
    free(problem);
}

void problem_calculate_min_costs_from_edges(Problem *problem) {
    for (int i = 0; i < network_get_num_servers(problem->network); i++)
        problem->dist_servers[i] = dijkstra_algorithm(network_get_graph(problem->network), network_get_server(problem->network, i));

    for (int i = 0; i < network_get_num_clients(problem->network); i++)
        problem->dist_clients[i] = dijkstra_algorithm(network_get_graph(problem->network), network_get_client(problem->network, i));

    for (int i = 0; i < network_get_num_monitors(problem->network); i++)
        problem->dist_monitors[i] = dijkstra_algorithm(network_get_graph(problem->network), network_get_monitor(problem->network, i));
}

double RTT(int a, int b, double *dists_a, double *dists_b) {
    return dists_a[b] + dists_b[a];
}

void problem_process_rtt(Problem *problem) {
    double min = 0;
    double rtt = 0;
    double rtt_star= 0;

    for (int i = 0; i < network_get_num_servers(problem->network); i++) {
        for (int j = 0; j < network_get_num_clients(problem->network); j++) {
            rtt = RTT(
                network_get_server(problem->network, i), 
                network_get_client(problem->network, j), 
                problem->dist_servers[i], 
                problem->dist_clients[j]
            );

            for (int k = 0; k < network_get_num_monitors(problem->network); k++) {
                rtt_star = RTT(
                    network_get_server(problem->network, i), 
                    network_get_monitor(problem->network, k), 
                    problem->dist_servers[i], 
                    problem->dist_monitors[k]
                ) + RTT(
                    network_get_monitor(problem->network, k), 
                    network_get_client(problem->network, j), 
                    problem->dist_monitors[k], 
                    problem->dist_clients[j]
                );

                if (rtt_star < min || k == 0) {
                    min = rtt_star;
                }
            }

            rtt_star = min;
            problem->round_trip_times[
                i * network_get_num_clients(problem->network) + j
            ] = round_trip_time_construct(
                network_get_server(problem->network, i), 
                network_get_client(problem->network, j), 
                rtt_star / rtt
            );
        }
    }
}

void problem_print(Problem *problem, char *output_file) {
    FILE *file = fopen(output_file, "w");
    if (file == NULL)
        exit(printf("Error: problem_print failed to open file.\n"));

    for (int i = 0; i < network_get_num_servers(problem->network) * network_get_num_clients(problem->network); i++) {
        fprintf(
            file, 
            "%d %d %.16lf\n", 
            round_trip_time_get_src(problem->round_trip_times[i]), 
            round_trip_time_get_dest(problem->round_trip_times[i]), 
            round_trip_time_get_rtt(problem->round_trip_times[i])
        );
    }

    fclose(file);
}

void problem_solve(Network *network, char *output_file) {
    Problem *problem = problem_construct(network);
    problem_calculate_min_costs_from_edges(problem);
    problem_process_rtt(problem);
    qsort(
        problem->round_trip_times, 
        network_get_num_servers(network) * network_get_num_clients(network), 
        sizeof(RoundTripTime *), 
        round_trip_compare
    );
    problem_print(problem, output_file);
    problem_destruct(problem);
}