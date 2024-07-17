#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main(int argc, char *argv[]) {
    // ./trab2 <path_input_file> <path_output_file>
    if (argc != 3)
        exit(printf("Error: invalid number of arguments.\n"));

    Graph *graph = graph_read(argv[1]);
    
    graph_print(graph);
    graph_destruct(graph);

    return 0;
}