#if !defined(_GRAPH_H_)
#define _GRAPH_H_


typedef struct Graph Graph;


/**
 * @brief Constrói um grafo.
 * @return Ponteiro para o grafo.
 */
Graph *graph_construct();

/**
 * @brief Destrói um grafo, liberando a memória alocada.
 * @param g Ponteiro para o grafo a ser destruído.
*/
void graph_destruct(Graph *g);

/**
 * @brief Lê um grafo de um arquivo.
 * @param graph Ponteiro para o grafo.
 * @param file Ponteiro para o arquivo.
 * @param num_nodes Número de nós.
 * @param num_edges Número de arestas.
 */
void graph_read(Graph *graph, FILE *file, int num_nodes, int num_edges);

/**
 * @brief Define o tipo de cada nó do grafo (servidor, cliente ou monitor).
 * @param graph Ponteiro para o grafo.
 * @param servers Vetor com os índices dos servidores.
 * @param clients Vetor com os índices dos clientes.
 * @param monitors Vetor com os índices dos monitores.
 * @param num_servers Número de servidores.
 * @param num_clients Número de clientes.
 * @param num_monitors Número de monitores.
 */
void graph_set_node_type(Graph *graph, int *servers, int *clients, int *monitors, int num_servers, int num_clients, int num_monitors);

/**
 * @brief Imprime as informações de um grafo.
 * @param graph Ponteiro para o grafo.
 */
void graph_print(Graph *graph);



#endif // _GRAPH_H_