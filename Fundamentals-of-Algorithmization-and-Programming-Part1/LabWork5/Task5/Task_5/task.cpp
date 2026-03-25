#pragma once
#include <iostream>
#include "../Task_5/iofuncs.h"
#include "../Task_5/mtrx.h"
#include "../Task_5/logic.h"

void task() {
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
        //основной алгос
        const int row = getMatrixRows();
        const int col = getMatrixCols();
        int** mtrx = initMatrix(row, col);
        int total;
        printMtrx(mtrx, row, col, total); 
        const int arr_size = total;
        if (!total) {
            std::cout << "Четные столбцы матрицы не содержат нечетных чисел\n";
            matrixFreeMemory(mtrx, row);
            mtrx = nullptr;
            continue;
        }
        std::cout << "Количествло нечетных элементов четных столбцов матрицы равно " << arr_size << '\n';
        int* arr = new int[total];
        //находим сумму элементов массива
        int sum = findSummaOfArrayElements(mtrx, arr, row, col, arr_size);
        //среднее значение
        double avrg = (double)sum / (double)arr_size;
        //чистим память и выводим результат
        printResult(arr_size, arr, avrg);
        delete[] arr; 
        arr = nullptr;
        matrixFreeMemory(mtrx, row);
        mtrx = nullptr;
    }
}