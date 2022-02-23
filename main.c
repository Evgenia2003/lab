#include <stdio.h>
#include <mm_malloc.h>
#include <stdbool.h>
#include <assert.h>
#include "libs/data_structures/vector/vector.h"
#include "libs/data_structures/matrix/matrix.h"
#include <math.h>

void swap_(void *a, void *b, size_t size) {
    char *pa = a;
    char *pb = b;
    for (size_t i = 0; i < size; i++) {
        char t = *pa;
        *pa = *pb;
        *pb = t;
        pa++;
        pb++;
    }
}

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

//задача 6
bool isMutuallyInverseMatrices(matrix m1, matrix m2) {
    matrix m = mulMatrices(m1, m2);
    bool result = isEMatrix(m);

    freeMemMatrix(m);

    return result;
}

//заадча 7
int max(int a, int b) {
    return a > b ? a : b;
}

long long findSumOfMaxesOfPseudoDiagonal(matrix m) {
    int size = m.nRows + m.nCols - 1;
    int maxEl[size];

    for (int i = 0; i < size; i++)
        maxEl[i] = 0;

    for (int i = 0; i < m.nCols; i++) {
        for (int j = 0; j < m.nRows; j++) {
            int index = i - j + m.nRows - 1;
            maxEl[index] = max (maxEl[index], m.values[j][i]);
        }
    }
    return getSum(maxEl, size);
}

//задача 8
int min(int a, int b) {
    return a < b ? a : b;
}

int getMinInArea(matrix m) {
    position minPos = getMaxValuePos(m);
    int minEl = m.values[minPos.rowIndex][minPos.colIndex];

    int left = minPos.colIndex;
    int right = minPos.colIndex;
    for (int i = minPos.rowIndex - 1; i >= 0; i--) {
        left = left > 0 ? left - 1 : left;
        right = right < m.nCols - 1 ? right + 1 : right;
        int minEl = min(getMin(&m.values[i][left], right - left + 1), minEl);
    }
    return minEl;
}

//задача 9
float getDistance(int *a, int n) {
    float distance = 0;
    for (int i = 0; i < n; i++) {
        distance += (float) (a[i] * a[i]);
    }
    return sqrtf(distance);
}

void insertionSortRowsMatrixByRowCriteriaF(matrix m, float (*criteria)(int *, int)) {
    float resultsCriteria[m.nRows];
    for (int i = 0; i < m.nRows; i++)
        resultsCriteria[i] = criteria(m.values[i], m.nCols);

    for (int i = 1; i < m.nRows; i++) {
        for (int j = i; j > 0 && resultsCriteria[j - 1] > resultsCriteria[j]; j--) {
            swap_(&resultsCriteria[j - 1], &resultsCriteria[j], sizeof(float));
            swapRows(m, j, j - 1);
        }
    }
}

void sortByDistances(matrix m) {
    insertionSortRowsMatrixByRowCriteriaF(m, getDistance);
}

//задача 10
int cmp_long_long(const void *pa, const void *pb) {
    long long arg1 = *(const long long *) pa;
    long long arg2 = *(const long long *) pb;

    if (arg1 < arg2)
        return -1;
    if (arg1 > arg2)
        return 1;
    return 0;
}

int countUnique(long long *a, int n) {
    if (n == 1)
        return 1;

    qsort(a, n, sizeof(long long), cmp_long_long);

    int countOfUnique = 1;
    for (int i = 1; i < n; i++) {
        if (a[i] != a[i - 1])
            countOfUnique++;
    }

    return countOfUnique;
}

int countEqClassesByRowsSum(matrix m) {
    long long sumRows[m.nRows];
    for (int i = 0; i < m.nRows; i++)
        sumRows[i] = getSum(m.values[i], m.nCols);

    return countUnique(sumRows, m.nRows);
}

//задача 11
int getNSpecialElement(matrix m) {
    int countSpecialEl = 0;

    for (int i = 0; i < m.nCols; i++) {
        int sumCol = 0;
        int maxEl = m.values[0][i];

        for (int j = 0; j < m.nRows; j++) {
            if (m.values[j][i] > maxEl)
                maxEl = m.values[j][i];
            sumCol += m.values[j][i];
        }
        sumCol -= maxEl;

        if (maxEl > sumCol)
            countSpecialEl++;
    }

    return countSpecialEl;
}

//задача 12
position getLeftMin(matrix m) {
    int minEl = m.values[0][0];
    position minPos = {0, 0};

    for (int i = 0; i < m.nCols; i++) {
        for (int j = 0; j < m.nRows; j++) {
            if (m.values[j][i] < minEl) {
                minEl = m.values[j][i];
                minPos = (position) {j, i};
            }
        }
    }

    return minPos;
}

//задача 13
bool isNonDescendingSorted(int *a, int n) {
    for (int i = 1; i < n; i++)
        if (a[i] < a[i - 1])
            return false;
    return true;
}

bool hasAllNonDescendingRows(matrix m) {
    for (int i = 0; i < m.nRows; i++)
        if (!isNonDescendingSorted(m.values[i], m.nCols))
            return false;
    return true;
}

int countNonDescendingRowsMatrices(matrix *ms, int nMatrix) {
    int count = 0;
    for (int i = 0; i < nMatrix; i++)
        if (hasAllNonDescendingRows(ms[i]))
            count++;
    return count;
}

//задача 14
int countValues(const int *a, int n, int value) {
    int count = 0;
    for (int i = 0; i < n; i++)
        if (a[i] == value)
            count++;
    return count;
}

int countZeroRows(matrix m) {
    int zeroRows = 0;
    for (int i = 0; i < m.nRows; i++)
        if (countValues(m.values[i], m.nCols, 0) == m.nCols)
            zeroRows++;
    return zeroRows;
}

void printMatrixWithMaxZeroRows(matrix *ms, int nMatrix) {
    int zeroRowsCount[nMatrix];
    for (int i = 0; i < nMatrix; i++)
        zeroRowsCount[i] = countZeroRows(ms[i]);

    int maxZeroRows = getMax(zeroRowsCount, nMatrix);

    for (int i = 0; i < nMatrix; i++)
        if (zeroRowsCount[i] == maxZeroRows)
            outputMatrix(ms[i]);
}

//задача 15
int getMatrixNorm(matrix m) {
    int norm = abs(m.values[0][0]);

    for (int i = 0; i < m.nRows; i++)
        for (int j = 0; j < m.nCols; j++)
            if (abs(m.values[i][j]) > norm)
                norm = abs(m.values[i][j]);

    return norm;
}

void printMatrixWithMinNorm(matrix *ms, int nMatrix) {
    int norms[nMatrix];

    for (int i = 0; i < nMatrix; i++)
        norms[i] = getMatrixNorm(ms[i]);

    int min = getMin(norms, nMatrix);
    for (int i = 0; i < nMatrix; i++)
        if (norms[i] == min)
            outputMatrix(ms[i]);
}

int main() {
    test();

    return 0;
}