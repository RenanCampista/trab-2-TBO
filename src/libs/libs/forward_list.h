#if !defined(_FORWARD_LIST_H)
#define _FORWARD_LIST_H

typedef void * data_type;
typedef struct Node Node;
typedef struct ForwardList ForwardList;
typedef struct ForwardListIterator ForwardListIterator;
struct ForwardListIterator {
    Node *current;
    ForwardList *list;
};

ForwardList *forward_list_construct();
void forward_list_destruct(ForwardList *forward_list, void (*data_destructor)(data_type));
int forward_list_size(ForwardList *forward_list);
void forward_list_push_back(ForwardList *forward_list, data_type data);
data_type forward_list_pop_back(ForwardList *forward_list);

void forward_list_iterator_init(ForwardListIterator *iterator, ForwardList *list);
data_type forward_list_iterator_next(ForwardListIterator *iterator);
int forward_list_iterator_has_next(ForwardListIterator *iterator);
#endif // _FORWARD_LIST_H