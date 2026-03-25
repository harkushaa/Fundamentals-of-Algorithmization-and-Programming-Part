#include <iostream>
#include <string>

#include "../header-files/logic.h"

#include "../../general/header-files/utils.h"
#include "../../general/header-files/constants.h"

using std::string;

void task1() {
    std::cout << "Задание 1. Перевести числа из прямого кода в обратный\n";
    while (true) {  // Потенциально O(m), где m - количество итераций
        std::cout << "Введите 1 для запуска программы, 0 для ее завершения:\n";
        int type = readIntegerInLine();
        if (type != 1 && type != 0) {
            std::cout << "Некорректный ввод\n";
            continue;
        }
        if (type == 0) {
            break;
        }
        std::cout << '\n';
        string n;
        while (true) {  // Потенциально O(k), где k - количество итераций для корректного ввода
          std::cout << "Введите ваше число:\n";
          n = readIntStringInLine();  // O(p), где p - длина строки ввода
          if (n == INFSTRING) {
            std::cout << "Некорректный ввод\n";
            continue;
          }
          break;
        }
        std::cout << '\n';
        string b = IntToBinary(n);  // O(q * r), где q - количество делений в IntToBinary, r - длина текущей строки на каждом шаге
        std::cout << "Представление введенного числа в прямом коде: " << b << '\n';
        string rev = ForwardToReverse(b, b.size());
        std::cout << "Представление введенного числа в обратном коде: " << rev << '\n' << '\n';
    }
}

