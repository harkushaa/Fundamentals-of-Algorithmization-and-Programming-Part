#include <iostream>
#include <cmath>
#include "../StaticLib/task1.h"

int main() {
    setlocale(LC_ALL, "Russian");
    std::cout << "Задание 1. Вариант 1. Составить программу для вычисления произведения одномерных динамических массивов(векторов)\n";
    std::cout << "Выполнил Гаркуша Игорь Вячеславович, группа 453502\n\n";

    while (true) {
        std::cout << "Введите 1 для запуска программы, 0 для завершения:\n";
        int type = readIntegerInLine();
        if (type != 1 && type != 0) {
            std::cout << "Некорректный ввод\n";
            continue;
        }
        if (type == 0) {
            break;
        }

        // Основной алгоритм
        solveProblem();
    }

    return 0;
}
