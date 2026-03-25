#pragma once
#include <iostream>
#include "../Task_4/iofuncs.h"
#include "../Task_4/mtrx.h"
#include "../Task_4/logic.h"

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
        //основной код
        const int row = getMatrixRows();
        const int col = getMatrixCols();
        double** mtrx = initMatrix(row, col);
        int total = 0;
        countNullElements(row, col, mtrx, total);
        if (!total) {
            std::cout << "В матрице не встречается нулевых элементов\n";
            matrixFreeMemory(mtrx, row);
            mtrx = nullptr;
            continue;
        }
        findNullElements(total, row, col, mtrx);
        makeTransposition(mtrx, row, col);
        matrixFreeMemory(mtrx, row);
        mtrx = nullptr;
    }
}