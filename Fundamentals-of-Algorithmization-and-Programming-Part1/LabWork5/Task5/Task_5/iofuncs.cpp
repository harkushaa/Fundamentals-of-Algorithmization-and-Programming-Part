#include <iostream>
#include "../Task_5/objects.h"

void printTask() {
    std::cout << "Задание 6. Создать динамический массив из элементов, расположенных в четных ";
    std::cout << "столбцах данного массива и имеющих нечетное значение.\n";
    std::cout << "Вычислить среднее арифметическое элементов динамического массива.\n";
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

int getMatrixRows() {
    int n;
    std::cout << "Введите количество строк массива:\n";
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
    std::cout << "Введите количество столбцов массива:\n";
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