#include <stdio.h>
#include "vector.h"
#include <mm_malloc.h>

vector createVector(size_t capacity) {
    int *data;
    if (capacity) {
        data = (int *) malloc(sizeof(int) * capacity);
        if (data == NULL) {
            fprintf(stderr, "bad alloc");
            exit(1);
        }
    } else {
        data = NULL;
    }
    return (vector) {data, 0, capacity};
}

void reserveVector(vector *v, size_t newCapacity) {
    if (newCapacity) {
        v->data = (int *) realloc(v->data, newCapacity * sizeof (int));
        if (v->data == NULL) {
            fprintf(stderr, "bad alloc");
            exit(1);
        } else {
            v->data = NULL;
        }
        v->capacity = newCapacity;
        if (v->size > v->capacity) {
            v->size = v->capacity;
        }
    }
}

void clearVector(vector *v) {
    v->size = 0;
}

void shrinkVectorToFit(vector *v) {
    reserveVector(v, v->size);
}

void deleteVector(vector *v) {
    free(v->data);
    v->capacity = 0;
    v->size = 0;
}
