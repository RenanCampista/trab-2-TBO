#include <stdio.h>
#include <stdlib.h>
#include "network.h"
#include "problem.h"

int main(int argc, char *argv[]) {
    // ./trab2 <path_input_file> <path_output_file>
    if (argc != 3)
        exit(printf("Error: invalid number of arguments.\n"));

    Network *network = network_read(argv[1]);
    problem_solve(network, argv[2]);
    network_destruct(network);

    return 0;
}