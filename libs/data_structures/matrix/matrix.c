#include "stdio.h"
#include "matrix.h"
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define ROWS 0
#define COLS 1

void inputArray_(int *const a, const size_t n) {
    for (size_t i = 0; i < n; i++)
        scanf("%d", &a[i]);
}

void outputArray_(const int *const a, const size_t n) {
    for (size_t i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

void swap(void *a, void *b, size_t size) {
    char *pa = a;
    char *pb = b;
    for (size_t i = 0; i < size; i++) {
        char tmp = *pa;
        *pa = *pb;
        *pb = tmp;
        pa += 1;
        pb += 1;
    }
}

matrix getMemMatrix(int nRows, int nCols) {
    int **values = (int **) malloc(sizeof(int *) * nRows);
    for (int i = 0; i < nRows; i++)
        values[i] = (int *) malloc(sizeof(int) * nCols);

    return (matrix) {values, nRows, nCols};
}

matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols) {
    matrix *ms = (matrix *) malloc(sizeof(matrix) * nMatrices);
    for (int i = 0; i < nMatrices; i++)
        ms[i] = getMemMatrix(nRows, nCols);
    return ms;
}

void freeMemMatrix(matrix m) {
    for (size_t i = 0; i < m.nRows; i++)
        free(m.values[i]);
    free(m.values);
}

void freeMemMatrices(matrix *ms, int nMatrices) {
    for (size_t i = 0; i < nMatrices; i++)
        freeMemMatrix(ms[i]);
    free(ms);
}

void inputMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++)
        inputArray_(m.values[i], m.nCols);
}

void inputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++)
        inputMatrix(ms[i]);
}

void outputMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++)
        outputArray_(m.values[i], m.nCols);
    printf("\n");
}

void outputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++)
        outputMatrix(ms[i]);
}

void indexOutOfRange(int size, int index) {
    if (index >= size) {
        fprintf(stderr, "Index {%d} out of the range", index);
        exit(2);
    }
}

void swapRows(matrix m, int i1, int i2) {
    indexOutOfRange(m.nRows, i1);
    indexOutOfRange(m.nRows, i2);

    swap(&m.values[i1], &m.values[i2], sizeof(int *));
}

void swapColumns(matrix m, int j1, int j2) {
    indexOutOfRange(m.nCols, j1);
    indexOutOfRange(m.nCols, j2);

    for (int i = 0; i < m.nRows; i++)
        swap(&m.values[i][j1], &m.values[i][j2], sizeof(int));
}

void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int *, int)) {
    int rowsCriteria[m.nRows];
    for (int i = 0; i < m.nRows; i++)
        rowsCriteria[i] = criteria(m.values[i], m.nCols);

    for (int i = 1; i < m.nRows; i++)
        for (int j = i; j > 0 && rowsCriteria[j - 1] > rowsCriteria[j]; j--) {
            swap(&rowsCriteria[j - 1], &rowsCriteria[j], sizeof(int));
            swapRows(m, j, j - 1);
        }
}

void insertionSortRowsMatrixByRowCriteriaF(matrix m, float (*criteria)(int *, int)) {
    float rowsCriteria[m.nRows];
    for (int i = 0; i < m.nRows; i++)
        rowsCriteria[i] = criteria(m.values[i], m.nCols);

    for (int i = 1; i < m.nRows; i++)
        for (int j = i; j > 0 && rowsCriteria[j - 1] > rowsCriteria[j]; j--) {
            swap(&rowsCriteria[j - 1], &rowsCriteria[j], sizeof(float));
            swapRows(m, j, j - 1);
        }
}

void insertionSortColsMatrixByColCriteria(matrix m, int (*criteria)(int *, int)) {
    int colsCriteria[m.nCols];
    for (int j = 0; j < m.nCols; j++) {
        int colsElem[m.nRows];
        for (int i = 0; i < m.nRows; i++)
            colsElem[i] = m.values[i][j];

        colsCriteria[j] = criteria(colsElem, m.nRows);
    }

    for (int i = 1; i < m.nCols; i++)
        for (int j = i; j > 0 && colsCriteria[j - 1] > colsCriteria[j]; j--) {
            swap(&colsCriteria[j - 1], &colsCriteria[j], sizeof(int));
            swapColumns(m, j, j - 1);
        }
}

bool isSquareMatrix(matrix m) {
    return m.nRows == m.nCols;
}

bool isTwoMatricesEqual(matrix m1, matrix m2) {
    bool isEqual = m1.nRows == m2.nRows && m1.nCols == m2.nCols ? true : false;

    for (size_t i = 0; i <  m1.nRows && isEqual; i++) {
        if (memcmp(m1.values[i], m2.values[i], sizeof(int) * m1.nCols) != 0)
            isEqual = false;
    }
    return isEqual;
}

bool isEMatrix(matrix m) {
    bool isEMatrix = isSquareMatrix(m) ? true : false;

    for (int i = 0; i < m.nRows && isEMatrix; i++)
        for (int j = 0; j < m.nCols && isEMatrix; j++)
            if (i != j && m.values[i][j] != 0 || i == j && m.values[i][i] != 1)
                isEMatrix = false;

    return isEMatrix;
}

bool isSymmetricMatrix(matrix m) {
    bool isSymmetric = isSquareMatrix(m) ? true : false;
    for (int i = 0; i < m.nRows && isSymmetric; i++)
        for (int j = 0; j < i && isSymmetric; j++)
            if (m.values[i][j] != m.values[j][i])
                isSymmetric = false;

    return isSymmetric;
}

void transposeSquareMatrix(matrix m) {
    if (!isSquareMatrix(m)) {
        fprintf(stderr, "not square matrix");
        exit(42);
    }

    for (int i = 0; i < m.nRows; i++)
        for (int j = i; j < m.nCols; j++)
            swap(&m.values[i][j], &m.values[j][i], sizeof(int));
}

position getMinValuePos(matrix m) {
    int min = m.values[0][0];
    position minPos = {0, 0};

    for (int i = 0; i < m.nRows; i++)
        for (int j = 0; j < m.nCols; j++)
            if (m.values[i][j] < min) {
                min = m.values[i][j];
                minPos.colIndex = j;
                minPos.rowIndex = i;
            }

    return minPos;
}

position getMaxValuePos(matrix m) {
    int max = m.values[0][0];
    position maxPos = {0, 0};

    for (int i = 0; i < m.nRows; i++)
        for (int j = 0; j < m.nCols; j++)
            if (m.values[i][j] > max) {
                max = m.values[i][j];
                maxPos.colIndex = j;
                maxPos.rowIndex = i;
            }

    return maxPos;
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

matrix mulMatrices(matrix m1, matrix m2) {
    if (m1.nCols != m2.nRows) {
        fprintf(stderr, "the number of rows is not equal to the number of columns");
        exit(3);
    }

    matrix product = getMemMatrix(m1.nRows, m2.nCols);

    for (int i = 0; i < m1.nRows; i++)
        for (int j = 0; j < m2.nCols; j++) {
            product.values[i][j] = 0;
            for (int k = 0; k < m2.nRows; k++)
                product.values[i][j] += m1.values[i][k] * m2.values[k][j];
        }
    return (matrix) product;
}