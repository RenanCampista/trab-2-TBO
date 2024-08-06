#include <stdio.h>
#include <stdlib.h>

#include "../libs/forward_list.h"


struct Node {
    int src;
    int dest;
    double cost;
    Node *next;
};

struct ForwardList {
    Node *head;
    int size;
};

struct ForwardListIterator {
    Node *node;
};


Node *node_construct(int src, int dest, double cost, Node *next) {
    Node *node = malloc(sizeof(Node));
    if (node == NULL)
        exit(printf("Error: node_construct: could not allocate memory.\n"));
    node->src = src;
    node->dest = dest;
    node->cost = cost;
    node->next = next;
    return node;
}

void node_destruct(Node *node) {
    free(node);
}

int node_get_src(Node *node) {
    return node->src;
}

int node_get_dest(Node *node) {
    return node->dest;
}

double node_get_cost(Node *node) {
    return node->cost;
}

ForwardList *forward_list_construct() {
    ForwardList *forward_list = calloc(1, sizeof(ForwardList));
    if (forward_list == NULL)
        exit(printf("Error: forward_list_construct: could not allocate memory.\n"));
    return forward_list;
}

void forward_list_destruct(ForwardList *forward_list) {
    Node *node = forward_list->head;
    while (node != NULL) {
        Node *next = node->next;
        node_destruct(node);
        node = next;
    }
    free(forward_list);
}

void forward_list_push_front(ForwardList *forward_list, int src, int dest, double cost) {
    forward_list->head = node_construct(src, dest, cost, forward_list->head);
    forward_list->size++;
}

void forward_list_pop_front(ForwardList *forward_list) {
    if (forward_list->head == NULL)
        return;
    Node *node = forward_list->head;
    forward_list->head = node->next;
    node_destruct(node);
    forward_list->size--;
}

int forward_list_size(ForwardList *forward_list) {
    return forward_list->size;
}

ForwardListIterator *iterator_init(ForwardList *forward_list) {
    ForwardListIterator *it = malloc(sizeof(ForwardListIterator));
    if (it == NULL)
        exit(printf("Error: forward_list_iterator_init: could not allocate memory.\n"));
    it->node = forward_list->head;
    return it;
}

void iterator_finish(ForwardListIterator *it) {
    free(it);
}

int iterator_has_next(ForwardListIterator *it) {
    return it->node != NULL;
}

Node *iterator_next(ForwardListIterator *it) {
    Node *node = it->node;
    it->node = it->node->next;
    return node;
}
