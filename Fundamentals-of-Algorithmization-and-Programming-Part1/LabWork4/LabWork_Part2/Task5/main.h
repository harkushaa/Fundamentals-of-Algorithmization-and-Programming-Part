#ifndef MAIN_H
#define MAIN_H

const int INF = 2000000000;

int readIntegerInLine();
char readCharInLine();
int getTotalMinesAround(char **field, int rows, int cols, int i, int j);
void printField(char **field, int rows, int cols);
void freeMemory(char **arr, int rows);

#endif