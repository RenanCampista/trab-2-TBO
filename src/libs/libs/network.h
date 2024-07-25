#if !defined(_NETWORK_H_)
#define _NETWORK_H_

#include "graph.h"

typedef struct Network Network;

Network *network_construct(int num_nodes, int num_servers, int num_clients, int num_monitors);

void network_destruct(Network *network);

int network_get_num_nodes(Network *network);

int network_get_num_servers(Network *network);

int network_get_num_clients(Network *network);

int network_get_num_monitors(Network *network);

int network_get_server(Network *network, int index);

int network_get_client(Network *network, int index);

int network_get_monitor(Network *network, int index);

Graph *network_get_graph(Network *network);

Network *network_read(char *file_name);

#endif // _NETWORK_H_
