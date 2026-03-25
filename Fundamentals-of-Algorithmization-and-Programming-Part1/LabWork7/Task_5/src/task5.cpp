#include <iostream>
#include <string>

#include "../../general/header-files/utils.h"
#include "../../general/header-files/constants.h"

#include "../header-files/funcs.h"

using std::string;

void task5() {
    std::cout << "Задание 5. Угадать отравленную бочку за 48 часов.\n";
    while (true) {
        std::cout << "Введите 1 для запуска программы, 0 для ее завершения:\n";
        int type = readIntegerInLine();
        if (type != 1 && type != 0) {
            std::cout << "Некорректный ввод\n";
            continue;
        }
        if (type == 0) {
            break;
        }
        int n;
        while (true) {  // Потенциально O(m), где m - количество итераций
            std::cout << "Введите номер бочки, которую желаете отравить:\n";
            n = readIntegerInLine();
            if (n == -INF) {
                std::cout << "Некорректный ввод\n";
                continue;
            }
            break;
        }
        //основной код
        ExecuteTask();
    }
}