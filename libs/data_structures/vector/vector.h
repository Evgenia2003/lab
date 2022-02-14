#ifndef UNTITLED_VECTOR_H
#define UNTITLED_VECTOR_H
#include <stdbool.h>

typedef struct vector {
    int *data;
    size_t size;
    size_t capacity;
} vector;

//возвращает структуру-дескриптор вектор из n значений
vector createVector(size_t capacity);

//изменяет количество памяти, выделенное под хранение элементов вектора
void reserveVector(vector *v, size_t newCapacity);

//удаляет элементы из контейнера, но не освобождает выделенную память
void clearVector(vector *v);

//освобождает память, выделенную под неиспользуемые элементы
void shrinkVectorToFit(vector *v);

//освобождает память, выделенную вектору
void deleteVector(vector *v);

//возвращает 1, если вектор v является пустым, иначе - 0
bool isEmpty(vector *v);

//возвращает 1, если вектор v является полным, иначе - 0
bool isFull( vector *v);

//возвращает i-ый элемент вектора v
int getVectorValue(vector *v, size_t i);

//добавляет элемент x в конец вектора v, если вектор заполнен, увеличивает количество выделенной ему памяти в 2 раза
void pushBack(vector *v, int x);

//удаляет последний элемент из вектора v
void popBack(vector *v);

//возвращает указатель на -ый элемент вектора v
int* atVector(vector *v, size_t index);

//возвращает указатель на последний элемент вектора v
int* back(vector *v);

//возвращает указатель на последний элемент вектора v
int* front(vector *v);

#endif