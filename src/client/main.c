#include <stdio.h>
#include <stdlib.h>

#include <time.h>

#include "../libs/libs/network.h"
#include "../libs/libs/problem.h"

int main(int argc, char *argv[]) {
    if (argc != 3)
        exit(printf("Error: invalid number of arguments.\n"));

    clock_t start, end;
    double cpu_time_used;

    start = clock();

    Network *network = network_read(argv[1]);
    if (network == NULL) {
        fprintf(stderr, "Error: failed to read network from file.\n");
        exit(EXIT_FAILURE);
    }
    problem_solve(network, argv[2]);
    network_destruct(network);

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Execution time: %f seconds\n", cpu_time_used);

    return 0;
}