#include <stdio.h>
#include <mm_malloc.h>
#include <stdbool.h>
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

//задача 4
matrix mulMatrices(matrix m1, matrix m2) {
    if (m1.nCols != m2.nRows) {
        fprintf(stderr, "error");
        exit(1);
    }
    matrix product = getMemMatrix(m1.nRows, m2.nCols);
    for (int i = 0; i < m1.nRows; i++)
        for(int j = 0; j < m2.nCols; j++) {
            product.values[i][j] = 0;
            for (int t = 0; t < m2.nRows; t++)
                product.values[i][j] += m1.values[i][t] * m2.values[t][j];
        }
    return (matrix) product;
}

void getSquareOfMatrixIfSymmetric(matrix *m) {
    if (isSymmetricMatrix(*m))
        *m = mulMatrices(*m, *m);
}

//задача 5
bool isUnique(long long *a, int n) {
    bool isUnique = true;
    for (int i = 0; i < n && isUnique; i++)
        for (int j = i + 1; j < n && isUnique; j++)
            if (a[i] == a[j])
                isUnique = false;
    return isUnique;
}

long long getSum(int *a, int n) {
    long long sum = 0;
    for (int i = 0; i < n; i++)
        sum += a[i];
    return sum;
}

void transposeIfMatrixHasNotEqualSumOfRows(matrix m) {
    long long sumRows[m.nRows];
    for (int i = 0; i < m.nRows; i++)
        sumRows[i] = getSum(m.values[i], m.nCols);
    if (isUnique(sumRows, m.nRows))
        transposeSquareMatrix(m);
}


int main() {
    test();

    return 0;
}