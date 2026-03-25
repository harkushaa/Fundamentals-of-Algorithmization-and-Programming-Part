#include <iostream>
#include "../Task_4/objects.h"

void printTask() {
    std::cout << "Задание 4. Определить, встречаются ли среди элементов динамичеси заданного массива нулевые значения\n";
    std::cout << "Если встречаются такие элементы, то определить их индексы и общее количество.\n";
    std::cout << "Переставить элементы этого массива в обратном порядке и вывести на экран.\n";
    std::cout << "Выполнил Гаркуша Игорь Вячеславович, группа 453502\n\n";
}

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

double readRealInLine() {
    double inputValue;
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
    std::cout << "Введите количество столбцов матрицы:\n";
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