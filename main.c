#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>


#include "libs/data_structures/matrix/matrix.h"

int randit(int a, int b) {
    srand(time(0));

    return rand() % b + a;
}

void test_getMemMatrix_rowsAndColsNotZero() {
    matrix m = getMemMatrix(5, 5);

    assert(m.nRows == 5);
    assert(m.nCols == 5);
    assert(m.values != NULL);

    size_t colsCount = m.nCols;
    for (size_t i = 0; i < colsCount; i++)
        assert(m.values[i] != NULL);

    freeMemMatrix(m);
}

void test_getMemMatrix_onRand() {
    int randRow = randit(1, 100);
    int randCol = randit(1, 100);

    matrix m = getMemMatrix(randRow, randCol);

    assert(m.nRows == randRow);
    assert(m.nCols == randCol);
    assert(m.values != NULL);

    size_t rowsCount = m.nRows;
    for (size_t i = 0; i < rowsCount; i++)
        assert(m.values[i] != NULL);

    freeMemMatrix(m);
}

void test_getMemMatrix() {
    test_getMemMatrix_rowsAndColsNotZero();
    test_getMemMatrix_onRand();
}

void test_twoMatricesEqual_equalMatrices() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 9,
            },
            3, 3);

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 9,
            },
            3, 3);

    assert(isTwoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_twoMatricesEqual_NotEqualElements() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 10,
            },
            3, 3);

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 9,
            },
            3, 3);

    assert(!isTwoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_twoMatricesEqual_NotEqualDimensions() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 2, 3, 2,
                    4, 5, 6, 3,
                    7, 8, 10, 4
            },
            3, 4);

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 9,
            },
            3, 3);

    assert(!isTwoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_twoMatricesEqual() {
    test_twoMatricesEqual_equalMatrices();
    test_twoMatricesEqual_NotEqualElements();
    test_twoMatricesEqual_NotEqualDimensions();
}

void test_swapRows_theSameRow() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 10
            },
            3, 3);

    swapRows(m, 1, 1);

    matrix result = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 10
            },
            3, 3);

    assert(isTwoMatricesEqual(m, result));

    freeMemMatrix(m);
    freeMemMatrix(result);
}

void test_swapRows_firstAndLastRectangle() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    1, 2, 3, 2,
                    4, 5, 6, 3,
                    7, 8, 10, 4
            },
            3, 4);

    swapRows(m, 0, m.nRows - 1);

    matrix result = createMatrixFromArray(
            (int[]) {
                    7, 8, 10, 4,
                    4, 5, 6, 3,
                    1, 2, 3, 2
            },
            3, 4);

    assert(isTwoMatricesEqual(m, result));

    freeMemMatrix(m);
    freeMemMatrix(result);
}

void test_swapRows_firstAndLastSquare() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 10
            },
            3, 3);

    swapRows(m, 0, m.nRows - 1);

    matrix result = createMatrixFromArray(
            (int[]) {
                    7, 8, 10,
                    4, 5, 6,
                    1, 2, 3
            },
            3, 3);

    assert(isTwoMatricesEqual(m, result));

    freeMemMatrix(m);
    freeMemMatrix(result);
}

void test_swapRows() {
    test_swapRows_firstAndLastRectangle();
    test_swapRows_firstAndLastSquare();
    test_swapRows_theSameRow();
}

void test_swapColumns_theSameColumn() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 10
            },
            3, 3);

    swapColumns(m, 1, 1);

    matrix result = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 10
            },
            3, 3);

    assert(isTwoMatricesEqual(m, result));

    freeMemMatrix(m);
    freeMemMatrix(result);
}

void test_swapColumns_firstAndLastSquare() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 10
            },
            3, 3);

    swapColumns(m, 0, m.nCols - 1);

    matrix result = createMatrixFromArray(
            (int[]) {
                    3, 2, 1,
                    6, 5, 4,
                    10, 8, 7
            },
            3, 3);

    assert(isTwoMatricesEqual(m, result));

    freeMemMatrix(m);
    freeMemMatrix(result);
}

void test_swapColumns_firstAndLastRectangle() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    1, 2, 3, 11,
                    4, 5, 6, 12,
                    7, 8, 10, 13
            },
            3, 4);

    swapColumns(m, 0, m.nCols - 1);

    matrix result = createMatrixFromArray(
            (int[]) {
                    11, 2, 3, 1,
                    12, 5, 6, 4,
                    13, 8, 10, 7
            },
            3, 4);

    assert(isTwoMatricesEqual(m, result));

    freeMemMatrix(m);
    freeMemMatrix(result);
}

void test_swapColumns() {
    test_swapColumns_theSameColumn();
    test_swapColumns_firstAndLastSquare();
    test_swapColumns_firstAndLastRectangle();
}

void test_isSquareMatrix_squareMatrix() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 10
            },
            3, 3);

    assert(isSquareMatrix(m));

    freeMemMatrix(m);
}

void test_isSquareMatrix_rectangleMatrix() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    1, 2, 3, 11,
                    4, 5, 6, 12,
                    7, 8, 10, 13
            },
            3, 4);

    assert(!isSquareMatrix(m));

    freeMemMatrix(m);
}

void test_isSquareMatrix() {
    test_isSquareMatrix_squareMatrix();
    test_isSquareMatrix_rectangleMatrix();
}

void test_isEMatrix_EMatrix() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    1, 0, 0,
                    0, 1, 0,
                    0, 0, 1
            },
            3, 3);

    assert(isEMatrix(m));

    freeMemMatrix(m);
}

void test_isEMatrix_EMatrix_notEMatrix() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    1, 0, 0,
                    0, 1, 0,
                    0, 0, 0
            },
            3, 3);

    assert(!isEMatrix(m));

    freeMemMatrix(m);
}

void test_isEMatrix() {
    test_isEMatrix_EMatrix();
    test_isEMatrix_EMatrix_notEMatrix();
}

void test_isSymmetricMatrix_EMatrix() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    1, 0, 0,
                    0, 1, 0,
                    0, 0, 1
            },
            3, 3);

    assert(isSymmetricMatrix(m));

    freeMemMatrix(m);
}

void test_isSymmetricMatrix_rectangleMatrix() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    1, 0, 0, 0,
                    0, 1, 0, 0,
                    0, 0, 1, 0
            },
            3, 4);

    assert(!isSymmetricMatrix(m));

    freeMemMatrix(m);
}

void test_isSymmetricMatrix_notSymmetricSquare() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    3, 0, 6,
                    0, 2, 3,
                    6, 4, 1
            },
            3, 3);

    assert(!isSymmetricMatrix(m));

    freeMemMatrix(m);
}

void test_isSymmetricMatrix_symmetricSquare() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    3, 0, 6,
                    0, 2, 4,
                    6, 4, 1
            },
            3, 3);

    assert(isSymmetricMatrix(m));

    freeMemMatrix(m);
}

void test_isSymmetricMatrix() {
    test_isSymmetricMatrix_rectangleMatrix();
    test_isSymmetricMatrix_EMatrix();
    test_isSymmetricMatrix_notSymmetricSquare();
    test_isSymmetricMatrix_symmetricSquare();
}

void test_transposeSquareMatrix_EMatrix() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 0, 0,
                    0, 1, 0,
                    0, 0, 1
            },
            3, 3);

    transposeSquareMatrix(m1);

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1, 0, 0,
                    0, 1, 0,
                    0, 0, 1
            },
            3, 3);

    assert(isTwoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_transposeSquareMatrix_SquareMartrix() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 9
            },
            3, 3);

    transposeSquareMatrix(m1);

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1, 4, 7,
                    2, 5, 8,
                    3, 6, 9
            },
            3, 3);

    assert(isTwoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_transposeSquareMatrix_transposeTransposeMatrix() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 9
            },
            3, 3);

    transposeSquareMatrix(m1);
    transposeSquareMatrix(m1);

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 9
            },
            3, 3);

    assert(isTwoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_transposeSquareMatrix() {
    test_transposeSquareMatrix_EMatrix();
    test_transposeSquareMatrix_SquareMartrix();
    test_transposeSquareMatrix_transposeTransposeMatrix();
}

void test_mulMatrices_Square() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 9,
            },
            3, 3);

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 9,
            },
            3, 3);

    matrix m3 = mulMatrices(m1, m2);

    matrix m4 = createMatrixFromArray(
            (int[]) {
                    30, 36, 42,
                    66, 81, 96,
                    102, 126, 150
            },
            3, 3);

    assert(isTwoMatricesEqual(m3, m4));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
    freeMemMatrix(m3);
    freeMemMatrix(m4);
}

void test_mulMatrices_toEMatrix() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 9,
            },
            3, 3);

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1, 0, 0,
                    0, 1, 0,
                    0, 0, 1,
            },
            3, 3);

    matrix m3 = mulMatrices(m1, m2);

    assert(isTwoMatricesEqual(m3, m1));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
    freeMemMatrix(m3);
}

void test_mulMatrices_rectangle() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    2, 1,
                    -3, 0,
                    4, -1,
            },
            3, 2);

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    5, -1, 6,
                    -3, 0, 7
            },
            2, 3);

    matrix m3 = mulMatrices(m1, m2);

    matrix m4 = createMatrixFromArray(
            (int[]) {
                    7, -2, 19,
                    -15, 3, -18,
                    23, -4, 17
            },
            3, 3);

    assert(isTwoMatricesEqual(m3, m4));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
    freeMemMatrix(m3);
    freeMemMatrix(m4);
}

void test_mulMatrices() {
    test_mulMatrices_Square();
    test_mulMatrices_toEMatrix();
    test_mulMatrices_rectangle();
}

void test_getMinValuePos_rectangle() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    2, 1,
                    -3, 0,
                    4, -1,
            },
            3, 2);

    position minPos = getMinValuePos(m1);
    assert(minPos.rowIndex == 1 && minPos.colIndex == 0);

    freeMemMatrix(m1);
}

void test_getMinValuePos_squareLastELemIsMin() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    2, 1, 2,
                    -3, 0, 3,
                    4, -1, -10
            },
            3, 3);

    position minPos = getMinValuePos(m1);
    assert(minPos.rowIndex == 2 && minPos.rowIndex == 2);

    freeMemMatrix(m1);
}

void test_getMinValuePos() {
    test_getMinValuePos_rectangle();
    test_getMinValuePos_squareLastELemIsMin();
}

void test_getMaxValuePos_rectangle() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    2, 1,
                    -3, 0,
                    4, -1,
            },
            3, 2);

    position maxPos = getMaxValuePos(m1);
    assert(maxPos.rowIndex == 2 && maxPos.colIndex == 0);

    freeMemMatrix(m1);
}

void test_getMaxValuePos_squareLastELemIsMax() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    -2, -11, -2,
                    -3, -4, -3,
                    -4, -1, 0
            },
            3, 3);

    position maxPos = getMaxValuePos(m1);
    assert(maxPos.rowIndex == 2 && maxPos.rowIndex == 2);

    freeMemMatrix(m1);
}

void test_getMaxValuePos() {
    test_getMaxValuePos_squareLastELemIsMax();
    test_getMaxValuePos_rectangle();
}

void test_createArrayOfMatrixFromArray_squareArray() {
    matrix *ma = createArrayOfMatrixFromArray(
            (int[]) {
                    -2, -11, -2,
                    -3, -4, -3,
                    -4, -1, 0,

                    7, 4, 45,
                    35, 17, 8,
                    6, 4, 2,

                    511, 16, 5,
                    20, 337, 712,
                    19, 2000, 147
            },
            3, 3, 3);

    matrix m1 = createMatrixFromArray(
            (int[]) {
                    -2, -11, -2,
                    -3, -4, -3,
                    -4, -1, 0
            },
            3, 3);

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    7, 4, 45,
                    35, 17, 8,
                    6, 4, 2,
            },
            3, 3);

    matrix m3 = createMatrixFromArray(
            (int[]) {
                    511, 16, 5,
                    20, 337, 712,
                    19, 2000, 147
            },
            3, 3);

    isTwoMatricesEqual(ma[0], m1);
    isTwoMatricesEqual(ma[1], m2);
    isTwoMatricesEqual(ma[2], m3);

    freeMemMatrix(m1);
    freeMemMatrix(m2);
    freeMemMatrix(m3);
    freeMemMatrices(ma, 3);
}

void test_createArrayOfMatrixFromArray_rectangleArray() {
    matrix *ma = createArrayOfMatrixFromArray(
            (int[]) {
                    -2, -11, -2,
                    -3, -4, -3,

                    7, 4, 45,
                    35, 17, 8,

                    511, 16, 5,
                    20, 337, 712
            },
            3, 2, 3);

    matrix m1 = createMatrixFromArray(
            (int[]) {
                    -2, -11, -2,
                    -3, -4, -3,
            },
            2, 3);

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    7, 4, 45,
                    35, 17, 8
            },
            2, 3);

    matrix m3 = createMatrixFromArray(
            (int[]) {
                    511, 16, 5,
                    20, 337, 712
            },
            2, 3);

    isTwoMatricesEqual(ma[0], m1);
    isTwoMatricesEqual(ma[1], m2);
    isTwoMatricesEqual(ma[2], m3);

    freeMemMatrix(m1);
    freeMemMatrix(m2);
    freeMemMatrix(m3);
    freeMemMatrices(ma, 3);
}

void test_createArrayOfMatrixFromArray() {
    test_createArrayOfMatrixFromArray_squareArray();
    test_createArrayOfMatrixFromArray_rectangleArray();
}


void test() {
    test_isSymmetricMatrix();
    test_getMemMatrix();
    test_twoMatricesEqual();
    test_swapRows();
    test_swapColumns();
    test_isSquareMatrix();
    test_isEMatrix();
    test_transposeSquareMatrix();
    test_mulMatrices();
    test_getMinValuePos();
    test_getMaxValuePos();
    test_createArrayOfMatrixFromArray();
}

int main() {

    test();

    return 0;
}
