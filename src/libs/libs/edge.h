#if !defined(_EDGE_H_)
#define _EDGE_H_

typedef struct Edge Edge;

Edge *edge_construct(int dest, double cost);

void edge_destruct(Edge *edge);

int edge_get_dest(Edge *edge);

double edge_get_cost(Edge *edge);

#endif // _EDGE_H_
