#if !defined(_ADJACENCY_MATRIX_H_)
#define _ADJACENCY_MATRIX_H_

typedef struct AdjacencyMatrix AdjacencyMatrix;


AdjacencyMatrix *adjacency_matrix_construct(int num_nodes);

void adjacency_matrix_destruct(AdjacencyMatrix *am);

void adjacency_matrix_add_cost(AdjacencyMatrix *am, int src, int dest, double cost);

int adjacency_matrix_get_num_nodes(AdjacencyMatrix *am);

double adjacency_matrix_get_cost(AdjacencyMatrix *am, int src, int dest);

#endif // _ADJACENCY_MATRIX_H_
