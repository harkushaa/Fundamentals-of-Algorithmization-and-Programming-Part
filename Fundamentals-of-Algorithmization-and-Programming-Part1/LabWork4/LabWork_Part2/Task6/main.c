#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "main.h"
#include <gtest/gtest.h>

int main() {
    printf("Задание 6. Сгенерировать магический квадрат\n");
    printf("Выполнил Гаркуша Игорь Вячеславович, группа 453502\n\n"); 
    while (true) {
        printf("Введите 1 для запуска программы, 0 для ее завершения:\n");
        unsigned int type = readIntegerInLine();
        if (type != 0 && type != 1) {
            printf("Некорректный ввод\n");
            continue;
        }
        if (type == 0) {
            break;
        }
        unsigned int n;
        printf("Введите размер магического квадрата (целое число больше 2):\n");
        while (true) {
            n = readIntegerInLine();
            if (n == -INF) {
                printf("Некорректный ввод\n");
                continue;
            }
            break;
        }
        const unsigned int size = n;
        //основной код
        unsigned int** a = (unsigned int**)malloc(size * size * sizeof(unsigned int*)); 
        for (unsigned int i = 0; i < size; i++) {
            a[i] = (unsigned int*)calloc(size, sizeof(unsigned int));
        }
        
        if (size % 2) {
            MethodForOdd(a, size);
        } else if (!(size % 4)) {
            MethodForEven(a, size);
        } else if (size % 4 == 2) {
            MethodForEvenEven(a, size);
        }
        //вывод
        for (unsigned int i = 0; i < size; i++) {
            for (unsigned int j = 0; j < size; j++) {
                printf("%u ", a[i][j]);
            }
            printf("\n");
        }   
        for (unsigned int i = 0; i < size; i++) {
            free(a[i]);
            a[i] = NULL;
        }
        free(a);
        a = NULL;
    }
    RUN_ALL_TESTS();
    return 0;
}

unsigned int readIntegerInLine() {
    unsigned int inputValue;
    char term;
    if (scanf("%d%c", &inputValue, &term) != 2 || term != '\n') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        return -INF;
    }
    return inputValue;
}  

void MethodForOdd(unsigned int **arr, unsigned int n) {
    arr[n / 2][n / 2 + 1] = 1;
    for (int k = 2, y = n / 2 + 2, z = n / 2 - 1; k <= n * n; k++) {
        if (z < 0) {
            z += n;
        }
        
        if (y > n - 1) {
            y -= n;
        }
        
        if (arr[z][y] == 0) {
            arr[z][y] = k;
        } else {
            y++;
            z++;
            
            if (z > n - 1) {
                z -= n;
            }
            
            if (y > n - 1) {
                y -= n;
            }
            
            if (arr[z][y] == 0) {
                arr[z][y] = k;
            }
        }
        
        z--;
        y++;
    }
}

void MethodForEven(unsigned int **arr, unsigned int n) {
    MethodForOdd(arr, n / 2);
    for (int z = 0; z < n / 2; z++) {
        for (int y = 0; y < n / 2; y++) {
            arr[z + n / 2][y + n / 2] = arr[z][y] + n * n / 4;
            arr[z][y + n / 2] = arr[z][y] + 2 * n * n / 4;
            arr[z + n / 2][y] = arr[z][y] + 3 * n * n / 4;
        }
    }

    int pillar = n / 2 - 3;

    for (int z = 0; z < n / 2; z++) {
        for (int y = (n / 2) - (pillar / 2); y < (n / 2) + (pillar / 2); y++) {
            int k;
            k = arr[z][y];
            arr[z][y] = arr[z + n / 2][y];
            arr[z + n / 2][y] = k;
        }
    }

    int k;
    k = arr[0][0];
    arr[0][0] = arr[n / 2][0];
    arr[n / 2][0] = k;

    k = arr[n / 2 - 1][0];
    arr[n / 2 - 1][0] = arr[n - 1][0];
    arr[n - 1][0] = k;

    for (int z = 1; z < n / 2 - 1; z++) {
        int k;
        k = arr[z][1];
        arr[z][1] = arr[z + n / 2][1];
        arr[z + n / 2][1] = k;
    }

}

void MethodForEvenEven(unsigned int **arr, unsigned int size) {
    //заполнение 1
    for (int i = 0; i < size; i += 4)
        for (int j = 0; j < size; j += 4)
            arr[i][j] = -1;

    for (int i = 0; i < size; i += 4)
        for (int j = 3; j < size; j += 4)
            arr[i][j] = -1;

    for (int i = 1; i < size; i += 4)
        for (int j = 1; j < size; j += 4)
            arr[i][j] = -1;

    for (int i = 1; i < size; i += 4)
        for (int j = 2; j < size; j += 4)
            arr[i][j] = -1;

    for (int i = 2; i < size; i += 4)
        for (int j = 1; j < size; j += 4)
            arr[i][j] = -1;

    for (int i = 2; i < size; i += 4)
        for (int j = 2; j < size; j += 4)
            arr[i][j] = -1;

    for (int i = 3; i < size; i += 4)
        for (int j = 0; j < size; j += 4)
            arr[i][j] = -1;

    for (int i = 3; i < size; i += 4)
        for (int j = 3; j < size; j += 4)
            arr[i][j] = -1;    

    //заполнение 2
    for (int i = 1, k = 0; k < size; k++) {
        for (int j = 0; j < size; j++) {
            if (arr[k][j] == 0) {
                arr[k][j] = i;
            }
            i++;
        }
    }
            
    for (long i = 1, k = size - 1; k >= 0; k--) {
        for (long j = size - 1; j >= 0; j--) {
            if (arr[k][j] == -1) {
                arr[k][j] = i;
            }
            i++;
        }
    }
}

// int* arr = (int*) malloc(10 * sizeof(int)); // Выделяет память для массива из 10 целых чисел
// int* ptr = new int;           // Выделение памяти для одного int без инициализации
// int* ptr = new int(5);        // Выделение памяти и инициализация значением 5
// int* arr = (int*) calloc(10, sizeof(int)); // Выделяет память для массива из 10 целых чисел и инициализирует нулями
// arr = (int*) realloc(arr, 20 * sizeof(int)); // Изменяет размер массива на 20 элементов