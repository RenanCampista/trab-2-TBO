#include <stdio.h>
#include <stdlib.h>

#include <time.h>

#include "../libs/include/network.h"
#include "../libs/include/problem.h"

int main(int argc, char *argv[]) {
    if (argc != 3)
        exit(printf("Error: invalid number of arguments.\n"));

    #ifdef DEBUG_MODE
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    #endif

    Network *network = network_read(argv[1]);
    problem_solve(network, argv[2]);
    network_destruct(network);

    #ifdef DEBUG_MODE
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", cpu_time_used);
    #endif
    
    return 0;
}