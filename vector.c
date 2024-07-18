
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"

static const int VECTOR_INIT_SIZE = 10;
static const int VECTOR_GROWTH_RATE = 2;

struct Vector {
    data_type *data;
    int size;
    int allocated;
};

Vector *vector_construct() {
    Vector *v = (Vector *)calloc(1, sizeof(Vector));
    if (v == NULL)
        exit(printf("Error: vector_construct: could not allocate memory.\n"));
        
    v->allocated = VECTOR_INIT_SIZE;
    v->size = 0;
    v->data = (data_type *)calloc(VECTOR_INIT_SIZE, sizeof(data_type));

    return v;
}

int vector_size(Vector *v) {
    return v->size;
}

data_type vector_get(Vector *v, int i) {
    if (i >= vector_size(v) || i < 0)
        exit(printf("Error: vector_get: invalid index %d for vector with size %d.\n", i, vector_size(v)));
    return v->data[i];
}

void vector_push_back(Vector *v, data_type val) {
    if (v->size >= v->allocated) {
        v->allocated *= VECTOR_GROWTH_RATE;
        v->data = (data_type *)realloc(v->data, v->allocated * sizeof(data_type));
    }

    v->data[v->size] = val;
    v->size++;
}

void vector_destruct(Vector *v) {
    free(v->data);
    free(v);
}