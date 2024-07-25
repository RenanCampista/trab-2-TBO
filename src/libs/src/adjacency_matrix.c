#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#include "../libs/adjacency_matrix.h"

struct AdjacencyMatrix {
    double **nodes;
    int num_nodes;
};


AdjacencyMatrix *adjacency_matrix_construct(int num_nodes) {
    AdjacencyMatrix *am = (AdjacencyMatrix *) calloc(1, sizeof(AdjacencyMatrix));
    if (am == NULL) 
        exit(printf("Error: adjacency_matrix_construct failed to allocate memory.\n"));

    am->nodes = (double **) calloc(num_nodes, sizeof(double*));
    am->num_nodes = num_nodes;

    for (int i = 0; i < num_nodes; i++) 
        am->nodes[i] = (double *) calloc(num_nodes, sizeof(double));

    return am;
}

void adjacency_matrix_destruct(AdjacencyMatrix *am) {
    for (int i = 0; i < am->num_nodes; i++) 
        free(am->nodes[i]);
    free(am->nodes);
    free(am);
}

void adjacency_matrix_add_cost(AdjacencyMatrix *am, int src, int dest, double cost) {
    am->nodes[src][dest] = cost;
}

int adjacency_matrix_get_num_nodes(AdjacencyMatrix *am) {
    return am->num_nodes;
}

double adjacency_matrix_get_cost(AdjacencyMatrix *am, int src, int dest) {
    return am->nodes[src][dest];
}