#include <iostream>
#include "main.h"

int main() {
    std::cout << "Задание 2. Вариант 6. Посчитать количество четных элементов главной и побочной диагоналей матрицы\n";
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
        int row; 
        while (true) {
            std::cout << "Введите количество строк матрицы:\n";
            row = readIntegerInLine();
            if (row <= 0) {
                std::cout << "Некорректный ввод\n";
                continue;
            }
            break;
        }
        int col; 
        while (true) {
            std::cout << "Введите количество столбцов матрицы:\n";
            col = readIntegerInLine();
            if (row <= 0) {
                std::cout << "Некорректный ввод\n";
                continue;
            }
            break;
        }
        int mtrx[row][col];
        int el;
        while (true) {
            std::cout << "Введите " << row * col << " элементов матрицы:\n";
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    while (true) {
                        el = readIntegerInLine();
                        if (el == -INF) {
                            std::cout << "Некорректный ввод\n";
                            continue;
                        }
                        mtrx[i][j] = el;
                        break;
                    }
                }
            }
            break;
        }
        int cnt1 = 0, cnt2 = 0;
        std::cout << "Исходная матрица:\n";
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                std::cout << mtrx[i][j] << '\t';
                if (mtrx[i][j] % 2 == 0) {
                    //главная диагональ
                    if (i == j) {
                        cnt1 += 1;
                    }
                    //побочная 
                    else if (i + j == col - 1) {
                        if (mtrx[i][j] % 2 == 0) {
                            cnt2 += 1;
                        }
                    }    
                }
            }
            std::cout << '\n';
        }
        std::cout << "Кол-во четных элементов главной диагонали: " << cnt1 << '\n';
        std::cout << "Кол-во четных элементов побочной диагонали: " << cnt2 << '\n';        
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