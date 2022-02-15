#include "stdio.h"
#include "matrix.h"
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define ROWS 0
#define COLS 1

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

matrix getMemMatrix(int nRows, int nCols){
    int **values = (int **) malloc(sizeof(int*)*nRows);
    for (int i = 0; i < nRows; i++)
        values[i] = (int *)malloc(sizeof(int )* nCols);
    return (matrix){values,nRows,nCols};
}

matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols){
    matrix *ms = (matrix *) malloc(sizeof(matrix) * nMatrices);
    for (int i = 0; i < nMatrices; i++)
        ms[i] = getMemMatrix(nRows, nCols);
    return ms;
}

void freeMemMatrix(matrix m){
    for (int i = 0; i < m.nRows; i++)
        free(m.values[i]);
    free(m.values);
}
void freeMemMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++)
        freeMemMatrix(ms[i]);
    free(ms);
}

void inputMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            scanf("%d", &m.values[i][j]);
        }
    }
}

void inputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        inputMatrix(ms[i]);
    }
}

void outputMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++) {
        printf("|");
        for (int j = 0; j < m.nCols; j++) {
            printf("%3.1d, ", m.values[i][j]);
        }
        printf("\b\b|\n");
    }
}

void outputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        outputMatrix(ms[i]);
        printf("\n");
    }
}

void swapRows(matrix m, int i1, int i2) {
    if (i1 >= m.nRows || i2 >= m.nRows) {
        fprintf(stderr, "matrix index out of range");
        exit(1);
    }

    int *t = m.values[i1];
    m.values[i1] = m.values[i2];
    m.values[i2] = t;
}

void swapColumns(matrix m, int j1, int j2) {
    if (j1 >= m.nCols || j2 >= m.nCols) {
        fprintf(stderr, "matrix index out of range");
        exit(1);
    }

    for (int i = 0; i < m.nRows; i++) {
        int t = m.values[i][j1];
        m.values[i][j1] = m.values[i][j2];
        m.values[i][j2] = t;
    }
}

void insertionSortMatrix(int a[], matrix *m, void (f)(matrix *, int, int)){
    for (int i = 1; i < m->nRows; ++i) {
        int k = i;
        while (k > 0 && a[i] >= a[k]){
            f(m, i, k);
            swap(&a[i], &a[k], sizeof(int));

            k--;
        }
    }
}

void insertionSortMatrixByCriteria(matrix *m, const int (*criteria)(int *, int), const int rowsOrCols){
    if (rowsOrCols == ROWS){
        int rowsArr[m->nRows];
        for (int i = 0; i < m->nRows; ++i)
            rowsArr[i] = criteria(m->values[i], m->nCols);

        insertionSortMatrix(rowsArr, m, swapRows);
    }
    else if (rowsOrCols == COLS){
        int colsArr[m->nCols];
        for (int i = 0; i < m->nCols; ++i) {
            int t[m->nRows];
            for (int j = 0; j < m->nRows; ++j)
                t[i] = m->values[j][i];

            colsArr[i] = criteria(t, m->nCols);
        }

        insertionSortMatrix(colsArr, m, swapColumns);
    }
}
bool isSquareMatrix(const matrix m){
    return m.nRows == m.nCols;
}

bool twoMatricesEqual(const matrix m1, const matrix m2){
    if (m1.nRows != m2.nRows || m1.nCols != m2.nCols)
        return false;

    for (int i = 0; i < m1.nRows; ++i)
        for (int j = 0; j < m1.nCols; ++j)
            if (m1.values[i][j] != m2.values[i][j])
                return false;

    return true;
}

bool isEMatrix(const matrix m){
    if (!isSquareMatrix(m))
        return false;

    for (int i = 0; i < m.nRows; ++i){
        if (m.values[i][i] != 1)
            return false;
        for (int j = 0; j < m.nCols; ++j)
            if (i != j && !m.values[i][j])
                return false;
    }

    return true;
}

bool isSymmetricMatrix(const matrix m){
    if (!isSquareMatrix(m))
        return false;

    for (int i = 1; i < m.nCols; ++i) {
        int t[m.nRows];
        for (int j = i; j < m.nRows; ++j)
            t[j] = m.values[j][i - 1];

        if (memcmp(m.values[i - 1] + i, t + i, m.nRows - i) != 0)
            return false;
    }

    return true;
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