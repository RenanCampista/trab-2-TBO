#if !defined(_GRAPH_H_)
#define _GRAPH_H_

#include "forward_list.h"


typedef struct Graph Graph;


/**
 * @brief Constrói um grafo.
 * 
 * @param num_nodes Número de nós do grafo.
 * @return Graph* Ponteiro para o grafo.
 */
Graph *graph_construct(int num_nodes);

/**
 * @brief Destrói um grafo.
 * 
 * @param graph Ponteiro para o grafo.
 */
void graph_destruct(Graph *graph);

/**
 * @brief Obtém o número de nós do grafo.
 * 
 * @param graph Ponteiro para o grafo.
 * @return int Número de nós.
 */
int graph_get_num_nodes(Graph *graph);

/**
 * @brief Adiciona uma aresta ao grafo.
 * 
 * @param graph Ponteiro para o grafo.
 * @param src Vértice de origem.
 * @param dest Vértice de destino.
 * @param cost Custo da aresta.
 */
void graph_add_edge(Graph *graph, int src, int dest, double cost);

/**
 * @brief Lê as arestas de um arquivo e adiciona ao grafo.
 * 
 * @param graph Ponteiro para o grafo.
 * @param file Ponteiro para o arquivo.
 * @param num_edges Número de arestas.
 */
void graph_read(Graph *graph, FILE *file, int num_edges);

/**
 * @brief Obtém as arestas de um nó (vértice).
 * 
 * @param graph Ponteiro para o grafo.
 * @param node Nó.
 * @return ForwardList* Ponteiro para a lista encadeada de arestas.
 */
ForwardList *graph_get_edges(Graph *graph, int node);

#endif // _GRAPH_H_
