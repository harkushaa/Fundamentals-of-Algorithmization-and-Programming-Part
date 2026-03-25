#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "main.h"

int main() {
    printf("Задание 5. Сгенерировать поле для игры в сапера\n");
    printf("Выполнил Гаркуша Игорь Вячеславович, группа 453502\n\n"); 
    while (true) {
        printf("Введите 1 для запуска программы, 0 для ее завершения:\n");
        int type = readIntegerInLine();
        if (type != 0 && type != 1) {
            printf("Некорректный ввод\n");
            continue;
        }
        if (type == 0) {
            break;
        }
        int n;
        printf("Введите ширину игрового поля:\n");
        while (true) {
            n = readIntegerInLine();
            if (n <= 1) {
                printf("Некорректный ввод\n");
                continue;
            }
            break;
        }
        int m;
        printf("Введите длину игрового поля:\n");
        while (true) {
            m = readIntegerInLine();
            if (m <= 1) {
                printf("Некорректный ввод\n");
                continue;
            }
            break;
        }
        //основной код
        const int rows = n, cols = m;
        char** field = (char **)malloc(rows * sizeof(char *));
        for (int i = 0; i < rows; i++) {
            field[i] = (char *)malloc(cols * sizeof(char));
        }
        char curr;
        while (true) {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    printf("Введите символ для заполнения игрового поля\n");
                    while (true) {
                        curr = readCharInLine();
                        if (curr != '.' && curr != '*') {
                            printf("Некорректный ввод\n");
                            continue;
                        }
                        field[i][j] = curr;
                        break;
                    }
                }
            }
            break;
        }
        //алгоритм для заполнения поля
        char** field_copy = (char **)malloc(rows * sizeof(char *));
        for (int i = 0; i < rows; i++) {
            field_copy[i] = (char *)malloc(cols * sizeof(char));
        }
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                field_copy[i][j] = field[i][j];
            }
        }
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (field[i][j] == '.') {
                    int total_mines_around = getTotalMinesAround(field, rows, cols, i, j);
                    field_copy[i][j] = '0' + total_mines_around;
                }
            }
        }
        freeMemory(field, rows);  //чистим память 
        printField(field_copy, rows, cols);
        freeMemory(field_copy, rows);  //чистим память 
    }
    return 0;
}

int readIntegerInLine() {
    int inputValue;
    char term;
    if (scanf("%d%c", &inputValue, &term) != 2 || term != '\n') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        return -INF;
    }
    return inputValue;
}  

char readCharInLine() {
    char inputValue;
    char term;
    if (scanf(" %c%c", &inputValue, &term) != 2 || term != '\n') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        return '\0';
    }
    return inputValue;
}

int getTotalMinesAround(char **field, int rows, int cols, int i, int j) {
    int total_mines_around = 0;
    for (int x = i - 1; x <= i + 1; x++) {
        for (int y = j - 1; y <= j + 1; y++) {
            if (x >= 0 && x <= rows - 1 && y >= 0 && y <= cols - 1 && !(x == i && y == j)) {
                if (field[x][y] == '*') {
                    total_mines_around++;
                }
            }
        }
    }
    return total_mines_around;
}

void printField(char **field, int rows, int cols) {
    printf("\n");
    printf("Сгенерированное поле:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%c\t", field[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void freeMemory(char **arr, int rows) {
    for (int i = 0; i < rows; i++) {
        free(arr[i]);
    }
    free(arr);
}