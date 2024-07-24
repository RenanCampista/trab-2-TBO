#if !defined(_GRAPH_H_)
#define _GRAPH_H_

typedef struct Graph Graph;


Graph *graph_construct(int num_nodes);

void graph_destruct(Graph *graph);

int graph_get_num_nodes(Graph *graph);

double graph_get_cost_from_edge(Graph *graph, int src, int dest);

void graph_add_edge(Graph *graph, int src, int dest, double cost);

void graph_read(Graph *graph, FILE *file, int num_edges);

#endif // _GRAPH_H_
