#if !defined(_FORWARD_LIST_H)
#define _FORWARD_LIST_H

typedef struct Node Node;
typedef struct ForwardList ForwardList;
typedef struct ForwardListIterator ForwardListIterator;


Node *node_construct(int src, int dest, long double cost, Node *next);
void node_destruct(Node *node);
int node_get_src(Node *node);
int node_get_dest(Node *node);
long double node_get_cost(Node *node);

ForwardList *forward_list_construct();
void forward_list_destruct(ForwardList *forward_list);
void forward_list_push_front(ForwardList *forward_list, int src, int dest, long double cost);
void forward_list_pop_front(ForwardList *forward_list);
int forward_list_size(ForwardList *forward_list);

ForwardListIterator *iterator_init(ForwardList *forward_list);
void iterator_destruct(ForwardListIterator *it);
int iterator_has_next(ForwardListIterator *it);
Node *iterator_next(ForwardListIterator *it);
#endif // _FORWARD_LIST_H