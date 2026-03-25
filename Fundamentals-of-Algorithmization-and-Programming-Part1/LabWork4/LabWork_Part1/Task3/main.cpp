#include <iostream>
#include "main.h"

int main() {
    std::cout << "Задание 3. Вариант 6. Для заданной целочисленной матрицы размером NxM вывести индексы всех её седловых точек\n";
    std::cout << "Выполнил Гаркуша Игорь, группа 453502\n";
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
        int N;
        while (true) {
            std::cout << "Введите значение для N:\n";
            N = readIntegerInLine();
            if (N <= 0) {
                std::cout << "Некорректный ввод\n";
                continue;
            }
            break;
        }
        int M; 
        while (true) {
            std::cout << "Введите значение для M:\n";
            M = readIntegerInLine();
            if (M <= 0) {
                std::cout << "Некорректный ввод\n";
                continue;
            }
            break;
        }
        int** mtrx = new int*[N];
        for (int i = 0; i < N; i++) {
            mtrx[i] = new int[M];
        }
        std::cout << "Введите элементы матрицы:\n";
        int curr;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                while (true) {
                    curr = readIntegerInLine();
                    if (curr == -INF) {
                        std::cout << "Некорректный ввод\n";
                        continue;
                    }
                    mtrx[i][j] = curr;
                    break;
                }
            }
        }     
        std::cout << "Заданная матрица имеет вид:\n";
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                std::cout << mtrx[i][j] << ' ';
            }
            std::cout << '\n';
        }
        getPoints(mtrx, N, M); 
        for (int i = 0; i < N; i++) {
            delete[] mtrx[i];
            mtrx[i] = nullptr;
        }
        delete[] mtrx;
        mtrx = nullptr;
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

void getPoints(int **mtrx, int N, int M) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int curr = mtrx[i][j];
            bool rowMax = true;
            for (int k = 0; k < M; k++) {
                if (mtrx[i][k] > curr) {
                    rowMax = false;
                    break;
                }
            }
            bool rowMin = true;
            for (int k = 0; k < M; k++) {
                if (mtrx[i][k] < curr) {
                    rowMin = false;
                    break;
                }
            }
            bool colMax = true;
            for (int k = 0; k < N; k++) {
                if (mtrx[k][j] > curr) {
                    colMax = false;
                    break;
                }
            }
            bool colMin = true;
            for (int k = 0; k < N; k++) {
                if (mtrx[k][j] < curr) {
                    colMin = false;
                    break;
                }
            }
            if ((rowMax && colMin) || (rowMin && colMax)) {
                std::cout << "Седловая точка\n";
                std::cout << "i = " << i << '\t' << "j = " << j << '\n';
            }
        }
    }
}