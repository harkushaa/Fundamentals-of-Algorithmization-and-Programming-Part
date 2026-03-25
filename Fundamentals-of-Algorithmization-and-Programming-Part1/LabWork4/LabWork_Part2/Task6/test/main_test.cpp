#include <gtest/gtest.h>

extern "C" {
    #include "../main.h"  
}

unsigned int calculateMagicConstant(unsigned int n) {
    return n * (n * n + 1) / 2;
}

bool isMagicSquare(unsigned int** arr, unsigned int n) {
    unsigned int magicConstant = calculateMagicConstant(n);

    //сheck rows
    for (unsigned int i = 0; i < n; i++) {
        unsigned int rowSum = 0;
        for (unsigned int j = 0; j < n; j++) {
            rowSum += arr[i][j];
        }
        if (rowSum != magicConstant) return false;
    }

    //сheck columns
    for (unsigned int j = 0; j < n; j++) {
        unsigned int colSum = 0;
        for (unsigned int i = 0; i < n; i++) {
            colSum += arr[i][j];
        }
        if (colSum != magicConstant) return false;
    }

    //сheck diagonals
    unsigned int mainDiagonalSum = 0, secondaryDiagonalSum = 0;
    for (unsigned int i = 0; i < n; i++) {
        mainDiagonalSum += arr[i][i];
        secondaryDiagonalSum += arr[i][n - i - 1];
    }
    if (mainDiagonalSum != magicConstant || secondaryDiagonalSum != magicConstant) return false;

    return true;
}

//magic square of size 3 
TEST(MagicSquareTests, OddSize3x3) {
    unsigned int size = 3;
    unsigned int** arr = (unsigned int**)malloc(size * sizeof(unsigned int*));
    for (unsigned int i = 0; i < size; i++) {
        arr[i] = (unsigned int*)calloc(size, sizeof(unsigned int));
    }

    MethodForOdd(arr, size);

    EXPECT_TRUE(isMagicSquare(arr, size));

    for (unsigned int i = 0; i < size; i++) {
        free(arr[i]);
    }
    free(arr);
}

//magic square of size 4
TEST(MagicSquareTests, DoublyEvenSize4x4) {
    unsigned int size = 4;
    unsigned int** arr = (unsigned int**)malloc(size * sizeof(unsigned int*));
    for (unsigned int i = 0; i < size; i++) {
        arr[i] = (unsigned int*)calloc(size, sizeof(unsigned int));
    }

    MethodForEvenEven(arr, size);

    EXPECT_TRUE(isMagicSquare(arr, size));

    for (unsigned int i = 0; i < size; i++) {
        free(arr[i]);
    }
    free(arr);
}

//a magic square of size 6
TEST(MagicSquareTests, SinglyEvenSize6x6) {
    unsigned int size = 6;
    unsigned int** arr = (unsigned int**)malloc(size * sizeof(unsigned int*));
    for (unsigned int i = 0; i < size; i++) {
        arr[i] = (unsigned int*)calloc(size, sizeof(unsigned int));
    }

    MethodForEven(arr, size);

    EXPECT_TRUE(isMagicSquare(arr, size));

    for (unsigned int i = 0; i < size; i++) {
        free(arr[i]);
    }
    free(arr);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
