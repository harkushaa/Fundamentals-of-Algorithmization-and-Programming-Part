#include <iostream>
#include "../Task_5/iofuncs.h"
#include "../Task_5/objects.h"

int ** initMatrix(const int& row, const int& col) {
    int** mtrx = new int* [row];
    for (int i = 0; i < row; ++i) {
        mtrx[i] = new int[col];
    }
    const int size = row * col;
    std::cout << "Введите " << size << " элементов матрицы:\n";
    double curr = -1;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            while (true) {
                curr = readIntegerInLine();
                if (curr == -INF) {
                    std::cout << "Некорректный ввод\n";
                    continue;
                }
                mtrx[i][j] = curr;
                break;
            }
        }
    }
    return mtrx;
}

void matrixFreeMemory(int** mtrx, const int& row) {
    for (int i = 0; i < row; ++i) {
        delete[] mtrx[i];
        mtrx[i] = nullptr;
    }
    delete[] mtrx;
}