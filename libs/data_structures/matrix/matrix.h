
#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <stdio.h>
#include <stdbool.h>

typedef struct matrix {
    int **values;       // элементы матрицы
    int nRows;          // количество рядов
    int nCols;          // количество столбцов
} matrix;

typedef struct position {
    int rowIndex;       // индекс ряда
    int colIndex;       // индекс столбца
} position;

void swap(void *a, void *b, size_t size);

void inputArray_(int *const a, const size_t n);

void outputArray_(const int *const a, const size_t n);

matrix getMemMatrix(int nRows, int nCols);

matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols);

void freeMemMatrix(matrix m);

void freeMemMatrices(matrix *ms, int nMatrices);

void inputMatrix(matrix m);

void inputMatrices(matrix *ms, int nMatrices);

void outputMatrix(matrix m);

void outputMatrices(matrix *ms, int nMatrices);

void swapRows(matrix m, int i1, int i2);

void swapColumns(matrix m, int j1, int j2);

void insertionSortRowsMatrixByRowCriteriaF(matrix m, float (*criteria)(int *, int));

void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int *, int));

void insertionSortColsMatrixByColCriteria(matrix m, int (*criteria)(int *, int));

matrix mulMatrices(matrix m1, matrix m2);

bool isSquareMatrix(matrix m);

bool isEMatrix(matrix m);

bool isTwoMatricesEqual(matrix m1, matrix m2);

bool isSymmetricMatrix(matrix m);

void transposeSquareMatrix(matrix m);

position getMinValuePos(matrix m);

position getMaxValuePos(matrix m);

matrix createMatrixFromArray(const int *a, int nRows, int nCols);

matrix *createArrayOfMatrixFromArray(const int *values, size_t nMatrices, size_t nRows, size_t nCols);

#endif
