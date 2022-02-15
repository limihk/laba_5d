
#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

typedef struct matrix{
    int **values;
    int nRows;
    int nCols;
}matrix;

typedef struct position{
    int rowIndex;
    int colIndex;
};

matrix getMemMatrix(int nRows, int nCols);

matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols);

void freeMemMatrices(matrix *ms, int nMatrices);

#endif
