#include <iostream>
#include "main.h"

int main() {
    std::cout << "Задание 1. Вариант 6. Сдвинуть элементы массива циклически на п позиций влево\n";
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

        int arrSize; 
        while (true) {
            std::cout << "Введите размерность массива:\n";
            arrSize = readIntegerInLine();
            if (arrSize <= 0) {
                std::cout << "Некорректный ввод\n";
                continue;
            }
            break;
        }
        int arr[arrSize];
        int curr_num;
        int i = 0; 
        printCorrect(arrSize);
        while (true) {
            if (i == arrSize) {
                break;
            }
            curr_num = readIntegerInLine();
            if (curr_num == -INF) {
                std::cout << "Некорректный ввод\n";
                continue;
            }
            arr[i] = curr_num;
            i += 1;
        }
        std::cout << "Исходный массив: "; 
        for (int i = 0; i < arrSize; i++) {

            std::cout << arr[i] << ' ';
        }
        std::cout << '\n';
        int k; 
        while (true) {
            std::cout << "Введите число k, на сколько элементов влево хотите сдвинуть:\n";
            k = readIntegerInLine();
            if (k < 0) {
                std::cout << "Некорректный ввод\n";
                continue;
            }
            break;
        }
        for (int i = 0; i < k; i++) {
            int temp = arr[0];
            for (int j = 1; j < arrSize; j++) {
                arr[j - 1] = arr[j];    
            }
            arr[arrSize - 1] = temp;
        }
        printCorrectShift(k); 
        for (int i = 0; i < arrSize; i++) {

            std::cout << arr[i] << ' ';
        }
        std::cout << '\n';
    }    
    return 0;
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
}

void printCorrect(int val) {
    int last_digit = val % 10, last_two = val % 100;
    if (last_digit == 1 && last_two != 11) {
        std::cout << "Введите " << val << " число для заполнения массива:\n";
    }
    else if (last_digit == 2 || last_digit == 3 || last_digit == 4) {
        std::cout << "Введите " << val << " числа для заполнения массива:\n";
    }
    else {
        std::cout << "Введите " << val << " чисел для заполнения массива:\n";
    }
    return;
}

void printCorrectShift(int k) {
    int last_digit = k % 10, last_two = k % 100;
    if (last_digit == 1 && last_two != 11) {
        std::cout << "Массив после " << k << " сдвига:\n";
    }
    else {
        std::cout << "Массив после " << k << " сдвигов:\n";
    }
    return;
}