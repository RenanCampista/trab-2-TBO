#if !defined(_GRAPH_H_)
#define _GRAPH_H_

typedef struct Graph Graph;

#include "../libs/forward_list.h"

Graph *graph_construct(int num_nodes);
void graph_destruct(Graph *graph);
int graph_get_num_nodes(Graph *graph);
void graph_add_edge(Graph *graph, int src, int dest, long double cost);
void graph_read(Graph *graph, FILE *file, int num_edges);
ForwardList *graph_get_edges(Graph *graph, int node);

#endif // _GRAPH_H_
