#if !defined(_EDGE_H_)
#define _EDGE_H_

typedef struct Edge Edge;

/**
 * @brief Cria uma nova aresta com o vizinho e peso especificados.
 * @param neighbor O número do vizinho.
 * @param cost O peso da aresta.
 * @return Ponteiro para a nova aresta.
*/
Edge* edge_construct(int neighbor, double cost);

/**
 * @brief Destrói uma aresta, liberando a memória alocada.
 * @param edge Ponteiro para a aresta a ser destruída.
*/
void edge_destruct(Edge *edge);

/**
 * @brief Retorna o número do vizinho de uma aresta.
 * @param edge Ponteiro para a aresta.
 * @return O número do vizinho.
*/
int edge_get_neighbor(Edge *edge);

/**
 * @brief Retorna o custo de uma aresta.
 * @param edge Ponteiro para a aresta.
 * @return O custo da aresta.
*/
double edge_get_cost(Edge *edge);


/**
 * @brief Imprime as informações de uma aresta.
 * @param edge Ponteiro para a aresta.
*/
void edge_print(Edge *edge);

#endif // _Edge_H_