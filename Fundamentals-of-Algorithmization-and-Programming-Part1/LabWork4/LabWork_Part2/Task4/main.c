#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "main.h"

int main() {
    printf("Задание 4. Определить диагональ с наибольшей суммой чисел\n");
    printf("Выполнил Гаркуша Игорь Вячеславович, группа 453502\n\n"); 
    while (true) { 
        printf("Введите 1 для запуска программы, 0 для ее завершения:\n");
        uint type = readIntegerInLine();
        if (type != 0 && type != 1) {
            printf("Некорректный ввод\n");
            continue;
        }
        if (type == 0) {
            break;
        }
        int s;
        printf("Введите размер трехмерного массива:\n");
        while (true) {
            s = readIntegerInLine();
            if (s <= 1) {
                printf("Некорректный ввод\n");
                continue;
            }
            break;
        }
        //основной код
        const uint size = s;
        const uint volume = size * size * size; 
        uint *arr = (uint*) malloc(volume * sizeof(uint));
        printCorrect(volume);
        int num;
        while (true) {
            for (uint i = 0; i < volume; i++) {
                while (true) {
                    num = readIntegerInLine();
                    if (num < 0) {
                        printf("Некорректный ввод\n");
                        continue;
                    }
                    arr[i] = num;
                    break;
                }
            }
            break;
        }
        printf("Исходный массив чисел\n");
        int cnt1 = 0, cnt2 = 0;
        int j_d2 = size - 1; 
        for (uint indx = 0; indx < volume; indx++) {
            uint i = indx / (size * size);
            uint j = (indx % (size * size)) / size;
            uint k = indx % size;

            if (k == 0 && j == 0) {
                printf("Слой массива №%d:\n", i + 1);
            }
            printf("%d ", arr[indx]);
            if (k == size - 1) {
                printf("\n");   
            }
            if (k == size - 1 && j == size - 1) {
                printf("\n");
            }
            //d1
            if (j == k && j == i && k == i) {
                cnt1 += arr[indx];
            }
            //d2
            if (j + k == size - 1 && j_d2 == j) {
                j_d2 -= 1;
                cnt2 += arr[indx];
            }
        }
        free(arr);
        arr = NULL;
        if (cnt1 == cnt2) {
            printf("Суммы элементов диагоналей равны\n%d = %d\n", cnt1, cnt2);
        } else if (cnt1 > cnt2) {
            printf("Сумма элементов первой диагонали больше\n%d > %d\n", cnt1, cnt2);
        } else {
            printf("Сумма элементов первой диагонали меньше второй\n%d < %d\n", cnt1, cnt2);
        }
    }
    return 0;
}

uint readIntegerInLine() {
    uint inputValue;
    char term;
    if (scanf("%d%c", &inputValue, &term) != 2 || term != '\n') {
        uint c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        return -INF;
    }
    return inputValue;
}  

void printCorrect(uint val) {
    uint last_digit = val % 10, last_two = val % 100;
    if (last_digit == 1 && last_two != 11) {
        printf("Введите %d число для заполнения массива\n", val);
    }
    else if (last_digit == 2 || last_digit == 3 || last_digit == 4) {
        printf("Введите %d числа для заполнения массива\n", val);
    }
    else {
        printf("Введите %d чисел для заполнения массива\n", val);
    }
}