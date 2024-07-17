#if !defined(_GRAPH_H_)
#define _GRAPH_H_


typedef struct Graph Graph;

/**
 * @brief Destrói um grafo, liberando a memória alocada.
 * @param g Ponteiro para o grafo a ser destruído.
*/
void graph_destruct(Graph *g);

/**
 * @brief Lê um grafo de um arquivo.
 * @param file_name Nome do arquivo.
 * @return Ponteiro para o grafo lido.
 */
Graph* graph_read(char* file_name);

/**
 * @brief Imprime as informações de um grafo.
 * @param graph Ponteiro para o grafo.
 */
void graph_print(Graph *graph);

#endif // _GRAPH_H_