#include <stdio.h>
#include "matrix.h"
#include <mm_malloc.h>

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

matrix getMemMatrix(int nRows, int nCols) {
    int **values = (int **) malloc(sizeof (int*) * nRows);
    for (int i = 0; i < nRows; i++)
        values[i] = (int *) malloc(sizeof (int) * nCols);
    return (matrix) {values, nRows, nCols};
}

matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols) {
    matrix *ms = (matrix*) malloc(sizeof (matrix) * nMatrices);
    for (int i = 0; i < nMatrices; i++)
        ms[i] = getMemMatrix(nRows, nCols);
    return ms;
}

void freeMemMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++)
        free(m.values[i]);
    free(m.values);
}

void freeMemMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++)
        freeMemMatrix((matrix) ms[i]);
}

void inputMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++)
        for (int j = 0; j < m.nCols; j++)
            scanf("%d", &(m.values[i][j]));
}

void inputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++)
        inputMatrix(ms[i]);
}

void outputMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++)
        for (int j = 0; j < m.nCols; j++)
            printf("%d", m.values[i][j]);
}

void outputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++)
        outputMatrix(ms[i]);
}

void swapRows(matrix m, int i1, int i2) {
    swap_(&m.values[i1], &m.values[i2], sizeof (int *));
}

void swapColumns(matrix m, int j1, int j2) {
    for (int i = 0; i < m.nRows; i++)
        swap_(&m.values[i][j1], &m.values[i][j2], sizeof (int *));
}

void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int*, int)) {
   int *criteriaArray = (int *) malloc (sizeof(int) * m.nRows);
   for (int i = 0; i < m.nRows; i++)
       criteriaArray[i] = criteria(m.values[i], m.nCols);
   for (int i = 0; i < m.nRows; i++){
       for (int j = i; j > 0 && criteriaArray[j - 1] > criteriaArray[j]; j--) {
           swap_(&criteriaArray[j - 1], &criteriaArray[j], sizeof (int));
           swapRows(m, j, j - 1);
       }
   }
   free(criteriaArray);
}

void insertionSortColsMatrixByColCriteria(matrix m, int (*criteria)(int*, int)) {
    int *criteriaArray = (int *) malloc(sizeof (int) * m.nCols);
    int *addArray = (int *) malloc(sizeof (int) * m.nRows);
    for (int i = 0; i < m.nCols; i++) {
        for (int j = 0; j < m.nRows; j++)
            addArray[j] = m.values[j][i];
        criteriaArray[i] = criteria(addArray, m.nRows);
    }
    for (int i = 0; i < m.nCols; i++) {
        for (int j = i; j > 0 && criteriaArray[j - 1] > criteriaArray[j]; j--) {
            swap_(&criteriaArray[j - 1], &criteriaArray[j], sizeof(int));
            swapColumns(m, j, j - 1);
        }
    }
    free(criteriaArray);
    free(addArray);
}

bool isSquareMatrix(matrix m) {
    return m.nRows == m.nCols;
}

bool areTwoMatricesEqual(matrix m1, matrix m2) {
    bool isEqual = (m1.nRows == m2.nRows && m1.nCols == m2.nCols) ? true : false;

    for (int i = 0; i < m1.nRows && isEqual; i++) {
        for (int j = 0; j < m1.nCols && isEqual; j++) {
            if (m1.values[i][j] != m2.values[i][j])
                isEqual = false;
        }
    }
    return isEqual;
}


bool isEMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++)
        for (int j = 0; j < m.nCols; j++) {
           if (i == j) {
               if (m.values[i][j] != 1)
                   return false;
           }
           else if (m.values[i][j] != 0)
               return false;
        }
    return true;
}

bool isSymmetricMatrix(matrix m) {
    bool isSymmetric = false;
    for (size_t i = 0; i < m.nRows; i++) {
        for (size_t j = 0; j < m.nCols; j++) {
            isSymmetric = (bool) (m.values[i][j] == m.values[j][i]);
            if (isSymmetric == 0)
                return false;
        }
    }
    return isSymmetric;
}

void transposeSquareMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++) {
        for (int j = i + 1; j < m.nCols; j++) {
            swap_(&m.values[i][j], &m.values[j][i], sizeof (int));
        }
    }
}

position getMinValuePos(matrix m) {
    position minIndex = {0, 0};
    int min = m.values[0][0];
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[i][j] < min) {
                min = m.values[i][j];
                minIndex = (position) {i, j};
            }
        }
    }
    return minIndex;
}

position getMaxValuePos(matrix m) {
    position maxIndex = {0, 0};
    int max = m.values[0][0];
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[i][j] > max) {
                max = m.values[i][j];
                maxIndex = (position) {i, j};
            }
        }
    }
    return maxIndex;
}

matrix createMatrixFromArray(const int *a, int nRows, int nCols) {
    matrix m = getMemMatrix(nRows, nCols);

    int k = 0;
    for (int i = 0; i < nRows; i++)
        for (int j = 0; j < nCols; j++)
            m.values[i][j] = a[k++];
    return m;
}

matrix *createArrayOfMatrixFromArray(const int *values, size_t nMatrices, size_t nRows, size_t nCols) {
    matrix *ms = getMemArrayOfMatrices(nMatrices, nRows, nCols);

    int l = 0;
    for (int k = 0; k < nMatrices; k++)
        for (int i = 0; i < nRows; i++)
            for (int j = 0; j < nCols; j++)
                ms[k].values[i][j] = values[l++];
    return ms;
}
