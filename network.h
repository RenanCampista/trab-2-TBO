#if !defined(_NETWORK_)
#define _NETWORK_

typedef struct Network Network;


/**
 * @brief Destrói uma rede, liberando a memória alocada.
 * @param network Ponteiro para a rede a ser destruída.
 */
void network_destruct(Network *network);

/**
 * @brief Lê uma rede de um arquivo.
 * @param file_name Nome do arquivo.
 * @return Ponteiro para a rede.
 */
Network *network_read(char *file_name);

/**
 * @brief Imprime as informações de uma rede.
 * @param network Ponteiro para a rede.
 */
void network_print(Network *network);

#endif // _NETWORK_
