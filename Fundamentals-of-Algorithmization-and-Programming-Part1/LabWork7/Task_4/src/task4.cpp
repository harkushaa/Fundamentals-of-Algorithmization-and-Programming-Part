#include <iostream>
#include <string>

#include "../../general/header-files/utils.h"
#include "../../general/header-files/constants.h"

#include "../header-files/logic.h"

using std::string;

void task4() {
    std::cout << "Задание 4. Разработать программу, которая проверяет, делится ли введенное пользователем число на заданное простое.\n";
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
        int number;
        while (true) {
            std::cout << "Введите число для проверки на делимость:\n";
            number = readIntegerInLine();
            if (number == -INF) {
                std::cout << "Некорректный ввод\n";
                continue;
            }
            break;
        }
        int prime;
        while (true) {
            std::cout << "Введите простое число (проверка делимости на него):\n";
            prime = readIntegerInLine();
            if (prime == -INF) {
                std::cout << "Некорректный ввод\n";
                continue;
            }
            if (isPrime(prime)) {
                break;
            }
            std::cout << "Число не простое\n";
            continue;
        }
        //основной код
        if (isDivisible(number, prime)) {
            std::cout << "Число " << number << " делится на число " << prime << '\n';
        }
        else {
            std::cout << "Число не делится на заданное простое" << '\n';
        }
    }
}