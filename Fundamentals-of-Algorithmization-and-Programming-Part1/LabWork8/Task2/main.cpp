#include "./app/header-files/app.h"
#include "./utils/header-files/utils.h"

int main() {    
    std::cout << "Лабораторная работа 8." << '\n' 
              << "Выполнил Гаркуша Игорь Вячеславович, студент группы 453502" << '\n'
              << "Задание 2. Реализовать программу для управления абитуриентами." << '\n' << '\n';
    int type;
    while (true) {
        std::cout << "Введите 1 для запуска программы, 0 для завершения: ";
        type = ReadIntegerInLine();
        if (type != 0 && type != 1) {
            std::cout << "Некорректный ввод" << '\n';
            continue;
        }
        if (type == 0) break;
        //начало работы программы
        AppRun(); 
    }  
    return 0;
}