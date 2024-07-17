#include <stdio.h>
#include <stdlib.h>

#include "node.h"

struct Node {
    Vector* edges;
    NodeType type;
};

Node *node_construct() {
    Node *node = (Node *) calloc(1, sizeof(Node));
    if (node == NULL)
        exit(printf("Error: node_construct failed to allocate memory.\n"));
    node->edges = vector_construct();
    node->type = UNDEFINED;
    return node;
}

void node_destruct(Node *node) {
    for (int i = 0; i < vector_size(node->edges); i++)
        edge_destruct((Edge *)vector_get(node->edges, i));
    vector_destruct(node->edges);
    free(node);
}

void node_add_edge(Node* node, int neighbor, double cost) {
    vector_push_back(node->edges, edge_construct(neighbor, cost));
}

Edge *node_get_edge(Node *node, int idx) {
    return (Edge *)vector_get(node->edges, idx);
}

int node_get_num_edges(Node *node) {
    return vector_size(node->edges);
}

void node_set_type(Node *node, int type) {
    if (type == 0)          node->type = SERVER;
    else if (type == 1)     node->type = CLIENT;
    else if (type == 2)     node->type = MONITOR;
    else                    node->type = UNDEFINED;
}

void node_print(Node *node) {
    printf("Node type: ");
    if (node->type == SERVER)        printf("Server\n");
    else if (node->type == CLIENT)   printf("Client\n");
    else if (node->type == MONITOR)  printf("Monitor\n");
    else                            printf("Undefined\n");

    for (int i = 0; i < vector_size(node->edges); i++)
        edge_print((Edge *)vector_get(node->edges, i));
    printf("\n");
}