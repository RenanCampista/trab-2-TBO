#ifndef PQ_H
#define PQ_H

typedef struct PQ PQ;


/**
 * @brief Inicializa uma Priority Queue.
 * 
 * @param maxN Número máximo de elementos na PQ.
 * @return PQ* Ponteiro para a PQ.
 */
PQ *PQ_init(int maxN);

/**
 * @brief Insere Item na PQ. A maior prioridade é a do Item com menor campo 'value'.
 * 
 * @param pq Ponteiro para a PQ.
 * @param data Dado do Item.
 * @param priority Prioridade do Item.
 */
void PQ_insert(PQ *pq, int data, double priority);

/**
 * @brief Remove Item com menor campo 'value' da PQ.
 * 
 * @param pq Ponteiro para a PQ.
 * @return int Dado do Item removido.
 */
int PQ_delmin(PQ *pq);

/**
 * @brief Muda a prioridade do nó com identificador 'id' para 'value'.
 * 
 * @param pq Ponteiro para a PQ.
 * @param id Identificador do nó.
 * @param value Nova prioridade.
 */
void PQ_decrease_key(PQ *pq, int id, double value);

/**
 * @brief Retorna True se a PQ não tem elementos.
 * 
 * @param pq Ponteiro para a PQ.
 * @return int True se a PQ não tem elementos.
 */
int PQ_empty(PQ *pq);

/**
 * @brief Libera memória.
 * 
 * @param pq Ponteiro para a PQ.
 */
void PQ_finish(PQ *pq);

#endif
