#include <iostream>
#include "../Task_4/iofuncs.h"
#include "../Task_4/objects.h"

void countNullElements(const int& row, const int& col, double**& mtrx, int& total) {
    std::cout << "Искомая матрица:\n";
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            std::cout << mtrx[i][j] << '\t';
            if (!(mtrx[i][j])) {
                total += 1;  
            }
        }
        std::cout << '\n';
    }
}

void findNullElements(int total, const int& row, const int& col, double**& mtrx) {
    std::cout << "Количество нулевых элементов матрицы равно: " << total << '\n';
    std::cout << "Индексы нулевых элементов в матрице: " << '\n';
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (!(mtrx[i][j])) {
                std::cout << "i = " <<  i << '\t' << "j = " << j << '\n';
            }
        }
    }
}

void makeTransposition(double**& mtrx, const int& row, const int& col) {
    std::cout << "Двумерный массив, перестановленный в обратном порядке:\n";
    for (int i = row - 1; i >= 0; i--) {
        for (int j = col - 1; j >= 0; j--) {
            std::cout << mtrx[i][j] << ' ';
        }
        std::cout << '\n';
    }
}
