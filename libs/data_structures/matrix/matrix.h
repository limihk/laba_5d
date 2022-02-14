
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


#endif
