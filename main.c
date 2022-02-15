#include <stdio.h>
#include <assert.h>
#include "libs/data_structures/vector/vector.h"
#include "libs/data_structures/matrix/matrix.h"

void test_pushBack_emptyVector() {
    vector v = createVector(0);
    pushBack(&v, 1);
    assert(v.data[0] == 1);
    assert(v.size == 1);
    assert(v.capacity == 1);
}

void test_pushBack_fullVector() {
    vector v = createVector(5);
    v.size = 5;
    pushBack(&v, 1);
    assert(v.data[5] == 1);
    assert(v.size == 6);
    assert(v.capacity == 10);
}

void test_popBack_notEmptyVector() {
    vector v = createVector(0);
    pushBack(&v, 10);

    assert(v.size == 1);
    popBack(&v);
    assert(v.size == 0);
    assert(v.capacity == 1);
}

void test_atVector_notEmptyVector() {
    vector vector1 = createVector(3);
    pushBack(&vector1, 1);
    pushBack(&vector1, 2);
    pushBack(&vector1, 3);
    assert(atVector(&vector1, 0) == &vector1.data[0]);
    assert(atVector(&vector1, 1) == &vector1.data[1]);
    assert(atVector(&vector1, 2) == &vector1.data[2]);
}

void test_atVector_requestToLastElement() {
    vector  vector1 = createVector(3);
    vector1.data[0] = 1;
    vector1.data[1] = 1;
    vector1.data[2] = 1;
    vector1.size = 3;
    assert(atVector(&vector1, 2) == &vector1.data[2]);
}

void test_back_oneElementInVector() {
    vector vector1 = createVector(1);
    vector1.data[0] = 1;
    assert(back(&vector1) == &vector1.data[0]);
}

void test_front_oneElementInVector() {
    vector vector1 = createVector(1);
    vector1.data[0] = 1;
    assert(front(&vector1) == &vector1.data[0]);
}

void test() {
    void test_pushBack_emptyVector();
    void test_pushBack_fullVector();
    void test_popBack_notEmptyVector();
    void test_atVector_notEmptyVector();
    void test_atVector_requestToLastElement();
    void test_back_oneElementInVector();
    void test_front_oneElementInVector();
}
//задача 1
void swapRowsMinAndMaxE(matrix m) {
    position min = getMinValuePos(m);
    position max = getMaxValuePos(m);
    swapRows(m, min.rowIndex, max.rowIndex);
}

//задача 2
int getMax(int *a, int n) {
    int maxValue = a[0];
    for (int i = 0; i < n; i++) {
        if (a[i] > maxValue)
            maxValue = a[i];
    }
    return maxValue;
}

void sortRowsByMaxElement(matrix m) {
    insertionSortRowsMatrixByRowCriteria(m, getMax);
}

//задача 3
int getMin(int *a, int n) {
    int minValue = a[0];
    for (int i = 0; i < n; i++) {
        if (a[i] < minValue)
            minValue = a[i];
    }
    return minValue;
}

void sortColsByMinElement(matrix m) {
    insertionSortColsMatrixByColCriteria(m, getMin);
}

int main() {
    test();

    return 0;
}