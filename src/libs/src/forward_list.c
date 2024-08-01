#include <stdio.h>
#include <stdlib.h>

#include "../libs/forward_list.h"

struct Node {
    data_type data;
    Node *next;
};

struct ForwardList {
    Node *head;
    int size;
};

Node *node_construct(Node *next, data_type data) {
    Node *node = (Node *) calloc(1, sizeof(Node));
    if (node == NULL)
        exit(printf("Error: node_construct: could not allocate memory.\n"));
    node->next = next;
    node->data = data;
    return node;
}

void node_destruct(Node *node, void (*data_destructor)(data_type)) {
    if (data_destructor != NULL)
        data_destructor(node->data);
    free(node);
}

ForwardList *forward_list_construct() {
    ForwardList *forward_list = (ForwardList *) calloc(1, sizeof(ForwardList));
    if (forward_list == NULL)
        exit(printf("Error: forward_list_construct: could not allocate memory.\n"));
    return forward_list;
}

void forward_list_destruct(ForwardList *forward_list, void (*data_destructor)(data_type)) {
    Node *it = forward_list->head;
    Node *next;
    for (int i = 0; i < forward_list->size; i++) {
        next = it->next;
        node_destruct(it, data_destructor);
        it = next;
    }
    free(forward_list);
}

int forward_list_size(ForwardList *forward_list) {
    return forward_list->size;
}

void forward_list_push_back(ForwardList *forward_list, data_type data) {
    Node *new_node = node_construct(NULL, data);
    if (forward_list->head == NULL) {
        forward_list->head = new_node;
        new_node->next = forward_list->head;
    } else {
        Node *last = forward_list->head;
        while (last->next != forward_list->head) {
            last = last->next;
        }
        last->next = new_node;
        new_node->next = forward_list->head;
    }
    forward_list->size++;
}

data_type forward_list_pop_back(ForwardList *forward_list) {
    Node *last = forward_list->head;
    Node *prev = NULL;
    while (last->next != forward_list->head) {
        prev = last;
        last = last->next;
    }
    data_type data = last->data;
    if (prev == NULL) {
        forward_list->head = NULL;
    } else {
        prev->next = forward_list->head;
    }
    node_destruct(last, NULL);
    forward_list->size--;
    return data;
}


void forward_list_iterator_init(ForwardListIterator *iterator, ForwardList *list) {
    iterator->list = list;
    iterator->current = list->head;
}

data_type forward_list_iterator_next(ForwardListIterator *iterator) {
    if (iterator->current == NULL)
        return (data_type)0;
    
    data_type data = iterator->current->data;
    iterator->current = iterator->current->next;
    if (iterator->current == iterator->list->head)
        iterator->current = NULL;

    return data;
}

int forward_list_iterator_has_next(ForwardListIterator *iterator) {
    return iterator->current != NULL;
}