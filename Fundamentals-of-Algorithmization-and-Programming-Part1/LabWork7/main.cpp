#include <iostream>

#include "./general/header-files/utils.h"

#include "./Task_1/header-files/task1.h"
#include "./Task_2/header-files/task2.h"
#include "./Task_3/header-files/task3.h"
#include "./Task_4/header-files/task4.h"
#include "./Task_5/header-files/task5.h"

int main() {
    std::cout << "Лабораторная работа 7. Вариант 6.\n";
    std::cout << "Выполнил Гаркуша Игорь Вячеславович, группа 453502\n\n";
    int type;
    while (true) {
        std::cout << "Список выполненных заданий:\n";
        std::cout << " - Задание 1 (для выбора нажмите 1)\n";
        std::cout << " - Задание 2 (для выбора нажмите 2)\n";  
        std::cout << " - Задание 3 (для выбора нажмите 3)\n";   
        std::cout << " - Задание 4 (для выбора нажмите 4)\n";
        std::cout << " - Задание 5 (для выбора нажмите 5)\n\n"; 
        std::cout << "для завершения работы ВСЕЙ программы - введите 0\n";
        type = readIntegerInLine();
        if (type != 0 && type != 1 && type != 2 && type != 3 && type != 4 && type != 5) {
            std::cout << "Некорректный ввод\n";
            continue;
        }
        if (type == 0) {
            break;
        }
        switch (type) {
            case 1: 
                task1();
            case 2: 
                task2();
            case 3:
                task3();
            case 4:
                task4();
            case 5:
                task5();
        }
    }
    return 0;
}