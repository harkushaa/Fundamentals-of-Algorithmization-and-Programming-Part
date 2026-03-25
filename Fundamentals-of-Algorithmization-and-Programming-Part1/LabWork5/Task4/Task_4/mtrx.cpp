#include <iostream>
#include "../Task_4/iofuncs.h"
#include "../Task_4/objects.h"

double** initMatrix(const int& row, const int& col) {
    double** mtrx = new double* [row];
    for (int i = 0; i < row; ++i) {
        mtrx[i] = new double[col];
    }
    const int size = row * col;
    std::cout << "Введите " << size << " элементов матрицы:\n";
    double curr = -1;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            while (true) {
                curr = readRealInLine();
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

void matrixFreeMemory(double** mtrx, const int& row) {
    for (int i = 0; i < row; ++i) {
        delete[] mtrx[i];
        mtrx[i] = nullptr;
    }
    delete[] mtrx;
}