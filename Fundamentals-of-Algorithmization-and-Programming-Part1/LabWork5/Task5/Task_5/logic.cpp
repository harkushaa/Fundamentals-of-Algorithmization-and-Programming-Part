#include <iostream>
#include <iomanip>
#include "../Task_5/iofuncs.h"
#include "../Task_5/objects.h"

void printMtrx(int**& mtrx, const int& size1, const int& size2, int& total) {
    total = 0;
    std::cout << "Исходная матрица:\n";
    for (int i = 0; i < size1; ++i) {
        for (int j = 0; j < size2; ++j) {
            std::cout << mtrx[i][j] << ' ';
            if (j % 2) {
                continue;
            }
            if (mtrx[i][j] % 2) {
                total += 1;
            }
        }
        std::cout << '\n';
    }
}

int findSummaOfArrayElements(int**& mtrx, int*& arr, const int& size1, const int& size2, const int& arr_size) {
    int indx = 0;
    int sum = 0;
    for (int i = 0; i < size1; ++i) {
        for (int j = 0; j < size2; ++j) {
            //если нечетный столбец
            if (j % 2) {
                continue;
            }
            //если четный столбец
            //если элемент сам со себе нечетный
            if (mtrx[i][j] % 2) {
                arr[indx] = mtrx[i][j];
                sum += mtrx[i][j];
                indx += 1;
            }
        }
    }
    return sum;
}

void printResult(const int& arr_size, int*& arr, double avrg) {
    std::cout << "Полученный массив чисел:\n";
    for (int i = 0; i < arr_size; ++i) {
        std::cout << arr[i] << ' ';
    }
    std::cout << '\n';
    std::cout << "Среднее арифмитическое его элементов: " << std::setprecision(2) << avrg << '\n';
}