#pragma once
int readIntegerInLine();
int getMatrixRows();
int getMatrixCols();
int** initMatrix(const int& row, const int& col);
void matrixFreeMemory(int** mtrx, const int& row);
void findEvenAndMultiply(const int& total, const int& row, const int& col, int** mtrx, int*& even_numbers, int& multiply);
void printResult(int total, int*& even_numbers, int multiply);