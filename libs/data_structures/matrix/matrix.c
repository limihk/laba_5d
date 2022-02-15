#include "stdio.h"
#include "matrix.h"
#include <malloc.h>
#include <stdlib.h>


static void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
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

