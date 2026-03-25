#include <iostream>
#include "../Task_3/funcs.h"

int main() {
    system("chcp 1251");
    setlocale(LC_ALL, "Russian");
    std::cout << "Задание 3. Создать динамическую матрицу. Вычислить произведение элементов главной диагонали матрицы\n";
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
        //задача
        const int row = getMatrixRows();
        const int col = getMatrixCols();
        //динамический массив
        int** mtrx = initMatrix(row, col);
        //количество четных элементов на главной диагонали
        int total = 0;
        std::cout << "Исходная матрица:\n";
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                std::cout << mtrx[i][j] << '\t';
                if (i == j && !(mtrx[i][j] % 2)) {
                    total += 1;
                }
            }
            std::cout << '\n';
        }
        if (!total) {
            std::cout << "Главная диагональ заданной матрицы не содержит четных чисел\n";
            matrixFreeMemory(mtrx, row);
            mtrx = nullptr;
            continue;
        }
        //умножение элементов и подсчет четных на главной диагонали
        int* even_numbers;
        int multiply;
        findEvenAndMultiply(total, row, col, mtrx, even_numbers, multiply);
        matrixFreeMemory(mtrx, row);
        mtrx = nullptr;
        printResult(total, even_numbers, multiply);
        delete[] even_numbers;
        even_numbers = nullptr;
    }
    return 0;
}