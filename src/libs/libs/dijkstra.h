#if !defined(_DIJKSTRA_H_)
#define _DIJKSTRA_H_

#include "graph.h"


/**
 * @brief Algoritmo de Dijkstra para encontrar o menor caminho entre um vértice de origem e todos os outros vértices do grafo.
 * 
 * @param graph Grafo.
 * @param src Vértice de origem.
 * @return double* Vetor de distâncias mínimas.
 */
double *dijkstra_algorithm(Graph *graph, int src);

#endif // _DIJKSTRA_H_
