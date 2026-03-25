#include <iostream>
#include "../Task_3/objects.h"

int readIntegerInLine() {
    int inputValue;
    if (!(std::cin >> inputValue) || (std::cin.peek() != '\n')) {
        std::cin.clear();
        while (std::cin.get() != '\n') {
        }
        return -INF;
    }
    return inputValue;
};

int getMatrixRows() {
    int n;
    std::cout << "Введите количество строк матрицы:\n";
    while (true) {
        n = readIntegerInLine();
        if (n <= 1) {
            std::cout << "Некорректный ввод\n";
            continue;
        }
        break;
    }
    return n;
}

int getMatrixCols() {
    int k;
    std::cout << "Введите количество строк матрицы:\n";
    while (true) {
        k = readIntegerInLine();
        if (k <= 1) {
            std::cout << "Некорректный ввод\n";
            continue;
        }
        break;
    }
    return k;
}

int** initMatrix(const int& row, const int& col) {
    int** mtrx = new int* [row];
    for (int i = 0; i < row; ++i) {
        mtrx[i] = new int[col];
    }
    const int size = row * col;
    std::cout << "Введите " << size << " элементов матрицы:\n";
    int curr = -1;
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

void findEvenAndMultiply(const int& total, const int& row, const int& col, int** mtrx, int*& even_numbers, int& multiply) {
    even_numbers = new int[total];
    multiply = 1;
    int indx = 0;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (i == j && !(mtrx[i][j] % 2)) {
                even_numbers[indx] = mtrx[i][j];
                multiply *= mtrx[i][j];
                indx += 1;
            }
        }
    }
}

void printResult(int total, int*& even_numbers, int multiply) {
    std::cout << "Исходный массив четных элементов главной диагонали матрицы:\n";
    for (int i = 0; i < total; ++i) {
        std::cout << even_numbers[i] << ' ';
    }
    std::cout << '\n';
    std::cout << "Произведение элементов массива равно: " << multiply << '\n';
}