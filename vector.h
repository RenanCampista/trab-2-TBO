#if !defined(_VECTOR_H_)
#define _VECTOR_H_

typedef void * data_type;
typedef struct Vector Vector;

/**
 * @brief Construct a new Vector object
 *  @return Ponteiro para o novo Vector.
*/
Vector *vector_construct();

/** @brief Adiciona um elemento no final do vetor.
 * @param v Ponteiro para a estrutura do Vector.
 *  @param val O valor a ser adicionado.
 */
void vector_push_back(Vector *v, data_type val);

/**
 * @brief Adiciona um elemento no início do vetor.
 * @param v Ponteiro para a estrutura do Vector.
 * @param val O valor a ser adicionado.
 * @return O elemento na posição i.
 */
data_type vector_get(Vector *v, int i);

/**
 * @brief Retorna o tamanho do vetor.
 * @param v Ponteiro para a estrutura do Vector.
 * @return O tamanho do vetor.
*/
int vector_size(Vector *v);

/**
 * @brief Desaloca o vetor.
 * @param v Ponteiro para a estrutura do Vector.
*/
void vector_destruct(Vector *v);

#endif // _VECTOR_H_