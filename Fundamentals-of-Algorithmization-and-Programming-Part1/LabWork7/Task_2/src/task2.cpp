#include <iostream>
#include <string>

#include "../../general/header-files/utils.h"
#include "../../general/header-files/constants.h"
#include "../header-files/logic.h"

using std::string;

void task2() {
    std::cout << "Задание 2. Произвести сложение двух чисел в дополнительном коде, результат вывести в прямом коде.\n";
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
        string number1;
        while (true) {  // Потенциально O(k), где k - количество итераций для корректного ввода
          std::cout << "Введите первое число число:\n";
          number1 = readIntStringInLine();  // O(p), где p - длина строки ввода
          if (number1 == INFSTRING) {
            std::cout << "Некорректный ввод\n";
            continue;
          }
          break;
        }
        string number2;
        while (true) {  // Потенциально O(k), где k - количество итераций для корректного ввода
          std::cout << "Введите второе число число:\n";
          number2 = readIntStringInLine();  // O(p), где p - длина строки ввода
          if (number2 == INFSTRING) {
            std::cout << "Некорректный ввод\n";
            continue;
          }
          break;
        }
        number1 = IntToBinary(number1);  // O(q * r), где q - количество делений в IntToBinary, r - длина текущей строки на каждом шаге
        number2 = IntToBinary(number2);  // O(q * r), где q - количество делений в IntToBinary, r - длина текущей строки на каждом шаге
        CallConvertBothToEqualSizes(number1, number1.size(), number2, number2.size());
        std::cout << '\n' << "Представление первого числа в прямом коде: " << number1[0] << '.' << number1.substr(1);
        std::cout << '\n' << "Представление второго числа в прямом коде: " << number2[0] << '.' << number2.substr(1) << '\n' << '\n';
        ConvertToForwardModifiedCode(number1, number2);
        string res = CalculateInAdditionalCode(number1, number2);
        if (res == INFSTRING) {
          std::cout << "Переполнение. Вычисление невозможно\n";
        }
        else {
          res = res.substr(1);
          std::cout << "Результат рассчетов равен:\n" << res[0] << '.' << res.substr(1) << '\n' << '\n';
        }
    }
}