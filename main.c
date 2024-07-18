#include <stdio.h>
#include <stdlib.h>
#include "network.h"

int main(int argc, char *argv[]) {
    // ./trab2 <path_input_file> <path_output_file>
    if (argc != 3)
        exit(printf("Error: invalid number of arguments.\n"));

    Network *network = network_read(argv[1]);
    network_print(network);
    network_destruct(network);
    
    return 0;
}