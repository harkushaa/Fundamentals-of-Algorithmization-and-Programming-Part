#include <iostream>
#include <string>

#include "../../general/header-files/utils.h"
#include "../../general/header-files/constants.h"
#include "../header-files/logic.h"

using std::string;

void task3() {
    std::cout << "Задание 3. Произвести сложение или вычитание двух чисел в заданной системе вычисления.\n";
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
        int base;
        while (true) {  // Потенциально O(k), где k - количество итераций для корректного ввода
            std::cout << "Введите систему счисления (от 2 до 260):\n";
            base = readIntegerInLine();
            if (base == -INF) {
                std::cout << "Некорректный ввод\n";
                continue;
            }
            break;
        }
        int operation;
        while (true) {
            std::cout << "Введите 1 для сложения, 2 для вычитания двух чисел:\n";
            operation = readIntegerInLine();
            if (operation != 1 && operation != 2 || operation == -INF) {
                std::cout << "Некорректный ввод\n";
                continue;
            }
            break;
        }

        //основной код
        string* encoding = new string[base];
        GenerateEncodingForChosenNumberSystem(base, encoding);
        
        //проверяем наполненность нашей кодировки
        /*
        std::cout << '\n' << "Ниже кодировка и целочисленный эквивалент каждого символа\n";
        std::cout << '\n' << "Символы для кодирования ваших чисел в выбранной системе будут выглядеть так:\n";
        for (unsigned int i = 0; i < base; ++i) {
            if (i % 13 == 0) {
                std::cout << '\n';
            }
            std::cout << encoding[i] << '^' << i << '^' << '\t';
        }*/

        bool isNegative1 = number1[0] == '-' ? true : false;
        number1 = isNegative1 ? number1.substr(1) : number1; // O(n)
        number1 = ConvertToChosenNumberSystem(number1, base, encoding);
        if (isNegative1) number1 = "-" + number1;  
        std::cout << '\n' << "Первое число, представленное в выбранной системе счисления: " << number1 << '\n';

        bool isNegative2 = number2[0] == '-' ? true : false;
        number2 = isNegative2 ? number2.substr(1) : number2;  // O(n)
        number2 = ConvertToChosenNumberSystem(number2, base, encoding);
        if (isNegative2) number2 = "-" + number2;
        std::cout << "Второе число: " << number2 << '\n'; 

        if (operation == 1) {
            string c = proccessOperation(number1, number2, encoding, base, true);
            bool isNegative3 = c[0] == '-' ? true : false; 
            c = isNegative3 ? c.substr(1) : c;  // O(n)
            
            if (isNegative3) {
                std::cout << "Сложение двух чисел:\n" << '-' <<  c << '\n';
                std::cout << '-' << ConvertFromEncodingToInteger(c, base) << '\n';
            }
            else {
                std::cout << "Сложение двух чисел:\n" << c << '\n';
                std::cout << ConvertFromEncodingToInteger(c, base) << '\n';
            }
        }
        if (operation == 2) {
            string d = proccessOperation(number1, number2, encoding, base, false);
            bool isNegative4 = d[0] == '-' ? true : false; 
            d = isNegative4 ? d.substr(1) : d;

            if (isNegative4) {
                std::cout << "Вычитание двух чисел:\n" << '-' << d << '\n';
                std::cout << '-' << ConvertFromEncodingToInteger(d, base) << '\n';
            }
            else {
                std::cout << "Вычитание двух чисел:\n" << d << '\n';
                std::cout << ConvertFromEncodingToInteger(d, base) << '\n';
            }
        }
    }
}