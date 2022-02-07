#ifndef UNTITLED_VECTOR_H
#define UNTITLED_VECTOR_H

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



#endif
