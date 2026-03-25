#include <iostream>
#include "task1.h"

int readIntegerInLine() {
    int inputValue;
    if (!(std::cin >> inputValue) || (std::cin.peek() != '\n')) {
        std::cin.clear();
        while (std::cin.get() != '\n') {
        }
        return -INF;
    }
    return inputValue;
}

double readDoubleInLine() {
    double inputValue;
    if (!(std::cin >> inputValue) || (std::cin.peek() != '\n')) {
        std::cin.clear();
        while (std::cin.get() != '\n') {
        }
        return -INF;
    }
    return inputValue;
}

void solveProblem() {
    double* arr1 = new double[size];
    double* arr2 = new double[size];

    double curr = -1;
    std::cout << "Введите 10 элементов массива:\n";
    for (int i = 0; i < size; ++i) {
        while (true) {
            curr = readDoubleInLine();
            if (curr == -INF) {
                std::cout << "Некорректный ввод\n";
                continue;
            }
            arr1[i] = curr;
            arr2[i] = 0.1 * tan(0.1 * i);
            break;
        }
    }

    double* arr3 = new double[size];
    for (int i = 0; i < size; i++) {
        arr3[i] = arr1[i] * arr2[i];
    }

    std::cout << "Результаты произведения векторов:\n";
    for (int i = 0; i < size; i++) {
        std::cout << arr3[i] << '\n';
    }

    // Чистим память
    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
}