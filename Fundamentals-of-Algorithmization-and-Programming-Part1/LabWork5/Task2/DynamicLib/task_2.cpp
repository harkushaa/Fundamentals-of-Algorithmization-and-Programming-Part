#include <iostream>
#include <cmath>
#include "../DynamicLib/task_2.h"

extern "C" {
    __declspec(dllexport) int readIntegerInLine() {
        int inputValue;
        if (!(std::cin >> inputValue) || (std::cin.peek() != '\n')) {
            std::cin.clear();
            while (std::cin.get() != '\n') {
            }
            return -INF;
        }
        return inputValue;
    }; 
    __declspec(dllexport) double readDoubleInLine() {
        double inputValue;
        if (!(std::cin >> inputValue) || (std::cin.peek() != '\n')) {
            std::cin.clear();
            while (std::cin.get() != '\n') {
            }
            return -INF;
        }
        return inputValue;
    };
    __declspec(dllexport) void fillArray(double* arr, int size) {
        std::cout << "Введите " << size - 1 << " элементов массива:\n";
        double curr;
        //первый элемент массива с индексом 0 заполняем 0
        arr[0] = 0;
        for (int i = 1; i < size; i++) {
            while (true) {
                curr = readDoubleInLine();
                if (curr == -INF) {
                    std::cout << "Некорректный ввод\n";
                    continue;
                }
                arr[i] = curr;
                break;
            }
        }
    }
    __declspec(dllexport) double getRecursiveSumHalf(double* arr, int indx1, int indx2) {
        if (indx1 == indx2) {
            return indx2;
        }
        return sin(arr[indx1]) * cos(arr[indx1]) * getRecursiveSumHalf(arr, indx1 + 1, indx2);
    };
    __declspec(dllexport) double getRecursiveSum(double* arr, int size, int step) {
        double res = 0;
        if (size == 2) {
            res = sin(arr[1]) * cos(arr[1]);
        }
        else {
            for (int i = 1; i < size; i += step) {
                res += getRecursiveSumHalf(arr, i, i + step - 1);
            }
        }
        return res;
    };
}