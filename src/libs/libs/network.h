#if !defined(_NETWORK_H_)
#define _NETWORK_H_

#include "graph.h"

typedef struct Network Network;


/**
 * @brief Destroi uma rede.
 * 
 * @param network Ponteiro para a rede.
 */
void network_destruct(Network *network);

/**
 * @brief Obtém o número de nós da rede.
 * 
 * @param network Ponteiro para a rede.
 * @return int Número de nós.
 */
int network_get_num_nodes(Network *network);


/**
 * @brief Obtém o número de servidores da rede.
 * 
 * @param network Ponteiro para a rede.
 * @return int Número de servidores.
 */
int network_get_num_servers(Network *network);


/**
 * @brief Obtém o número de clientes da rede.
 * 
 * @param network Ponteiro para a rede.
 * @return int Número de clientes.
 */
int network_get_num_clients(Network *network);


/**
 * @brief Obtém o número de monitores da rede.
 * 
 * @param network Ponteiro para a rede.
 * @return int Número de monitores.
 */
int network_get_num_monitors(Network *network);


/**
 * @brief Obtém o servidor de índice especificado.
 * 
 * @param network Ponteiro para a rede.
 * @param index Índice do servidor.
 * @return int Servidor.
 */
int network_get_server(Network *network, int index);


/**
 * @brief Obtém o cliente de índice especificado.
 * 
 * @param network Ponteiro para a rede.
 * @param index Índice do cliente.
 * @return int Cliente.
 */
int network_get_client(Network *network, int index);


/**
 * @brief Obtém o monitor de índice especificado.
 * 
 * @param network Ponteiro para a rede.
 * @param index Índice do monitor.
 * @return int Monitor.
 */
int network_get_monitor(Network *network, int index);


/**
 * @brief Obtém o grafo da rede.
 * 
 * @param network Ponteiro para a rede.
 * @return Graph* Ponteiro para o grafo.
 */
Graph *network_get_graph(Network *network);


/**
 * @brief Lê uma rede de um arquivo.
 * 
 * @param file_name Nome do arquivo.
 * @return Network* Ponteiro para a rede.
 */
Network *network_read(char *file_name);

#endif // _NETWORK_H_
