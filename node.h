#if !defined(_NODE_H_)
#define _NODE_H_
#include "vector.h"
#include "edge.h"

typedef struct Node Node;

typedef enum {
    UNDEFINED = -1,
    SERVER = 0,
    CLIENT = 1,
    MONITOR = 2
} NodeType;


/**
 * @brief Cria um novo nó.
 * @return Ponteiro para o novo nó.
*/
Node *node_construct();

/**
 * @brief Destrói um nó, liberando a memória alocada.
 * @param node Ponteiro para o nó a ser destruído.
*/
void node_destruct(Node *node);

/**
 * @brief Adiciona uma aresta ao nó.
 * @param node Ponteiro para o nó.
 * @param neighbor O nó vizinho.
 * @param cost O custo da aresta.
*/
void node_add_edge(Node* node, int neighbor, double cost);

/**
 * @brief Retorna uma aresta do nó.
 * @param node Ponteiro para o nó.
 * @param idx O índice da aresta.
 * @return Ponteiro para a aresta.
*/
Edge *node_get_edge(Node *node, int idx);

/**
 * @brief Retorna o número de arestas de um nó.
 * @param node Ponteiro para o nó.
 * @return O número de arestas.
*/
int node_get_num_edges(Node *node);

/**
 * @brief Define o tipo de um nó (servidor, cliente ou monitor).
 * @param node Ponteiro para o nó.
 * @param type O tipo do nó.
*/
void node_set_type(Node *node, int type);

/**
 * @brief Imprime as informações de um nó.
 * @param node Ponteiro para o nó.
*/
void node_print(Node *node);

#endif // _NODE_H_