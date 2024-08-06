#if !defined(_FORWARD_LIST_H)
#define _FORWARD_LIST_H

typedef struct Edge Edge;
typedef struct ForwardList ForwardList;
typedef struct ForwardListIterator ForwardListIterator;


/**
 * @brief Obtém o vértice de origem de uma aresta.
 * 
 * @param node Ponteiro para o nó da lista encadeada.
 */
int edge_get_src(Edge *edge);


/**
 * @brief Obtém o vértice de destino de uma aresta.
 * 
 * @param node Ponteiro para o nó da lista encadeada.
 * @return int Vértice de destino.
 * @return int Vértice de destino.
 */
int edge_get_dest(Edge *edge);

/**
 * @brief Obtém o custo de uma aresta.
 * 
 * @param node Ponteiro para o nó da lista encadeada.
 * @return double Custo da aresta.
 */
double edge_get_cost(Edge *edge);


/**
 * @brief Constrói uma lista encadeada.
 * 
 * @return ForwardList* Ponteiro para a lista encadeada.
 */
ForwardList *forward_list_construct();

/**
 * @brief Destrói uma lista encadeada.
 * 
 * @param forward_list Ponteiro para a lista encadeada.
 */
void forward_list_destruct(ForwardList *forward_list);

/**
 * @brief Insere uma aresta no início da lista encadeada.
 * 
 * @param forward_list Ponteiro para a lista encadeada.
 * @param src Vértice de origem.
 * @param dest Vértice de destino.
 * @param cost Custo da aresta.
 */
void forward_list_push_front(ForwardList *forward_list, int src, int dest, double cost);


/**
 * @brief Inicializa um iterador para a lista encadeada.
 * 
 * @param forward_list Ponteiro para a lista encadeada.
 * @return ForwardListIterator* Ponteiro para o iterador.
 */
ForwardListIterator *iterator_init(ForwardList *forward_list);

/**
 * @brief Finaliza o iterador.
 * 
 * @param it Ponteiro para o iterador.
 */
void iterator_finish(ForwardListIterator *it);

/**
 * @brief Verifica se o iterador tem um próximo elemento.
 * 
 * @param it Ponteiro para o iterador.
 * @return int 1 se tiver um próximo elemento, 0 caso contrário.
 */
int iterator_has_next(ForwardListIterator *it);

/**
 * @brief Obtém o próximo elemento do iterador.
 * 
 * @param it Ponteiro para o iterador.
 * @return Edge* Ponteiro para a aresta.
 */
Edge *iterator_next(ForwardListIterator *it);
#endif // _FORWARD_LIST_H