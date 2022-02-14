#include <stdio.h>
#include "vector.h"
#include <mm_malloc.h>
#include <stdbool.h>

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

bool isEmpty(vector *v) {
    return v->size == 0;
}

bool isFull( vector *v) {
    return v->size == v->capacity;
}

int getVectorValue(vector *v, size_t i) {
    return (i < v->size) ? v->data[i] : -1;
}

void pushBack(vector *v, int x) {
    if (isFull(v)) {
        reserveVector(v, v->capacity ? v->capacity * 2 : 1);
    }
    v->data[v->size] = x;
    v->size++;
}

void popBack(vector *v) {
    if (isEmpty(v)) {
        fprintf(stderr, "empty vector");
        exit(1);
    }
    v->size--;
}

int* atVector(vector *v, size_t index) {
    if (index >= v->size) {
        fprintf(stderr, "IndexError: a[%zu] is not exists", index);
        exit(1);
    }
    return v->data + index;
}

int* back(vector *v) {
    if (v->size == 0) {
        fprintf(stderr, "IndexError: empty vector");
        exit(1);
    }
    return v->data;
}

int* front(vector *v) {
    if (v->size == 0) {
        fprintf(stderr, "IndexError: empty vector");
        exit(1);
    }
    return v->data;
}