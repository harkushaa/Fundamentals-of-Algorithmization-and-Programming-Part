#include <iostream>
#include <Windows.h>
#include "../DynamicLib/task_2.h"

int main() {
    setlocale(LC_ALL, "RU");
	std::cout << "Задание 2. Для заданного одномерного массива найти сумму выражений, вычисляемых по формуле .\n";
	std::cout << "Выполнил Гаркуша Игорь Вячеславович, группа 453502\n\n\n\n";
    HINSTANCE load;
    load = LoadLibrary(L"DynamicLib.dll");
    typedef int (*readInteger) ();
    readInteger readInt;
    readInt = (readInteger)GetProcAddress(load, "readIntegerInLine");
    typedef void (*fillArr) (double* arr, int size);
    fillArr arrayFiller;
    arrayFiller = (fillArr)GetProcAddress(load, "fillArray");
    typedef double (*recursSumma) (double* arr, int size, int step);
    recursSumma recursSum;
    recursSum = (recursSumma)GetProcAddress(load, "getRecursiveSum");
    while (true) {
        std::cout << "Введите 1 для запуска программы, 0 для завершения:\n";
        int type = readInt();
        if (type != 0 && type != 1) {
            std::cout << "Некорректный ввод\n\n";
            continue;
        }
        if (type == 0) {
            break;
        }
        int size;
        std::cout << "Введит размер массива:\n";
        while (true) {
            size = readInt();
            if (size <= 0) {
                std::cout << "Некорректный ввод\n";
                continue;
            }
            break;
        }
        int step = size / 2;
        size += 1;
        double* arr = new double[size];
        arrayFiller(arr, size);
        double res = recursSum(arr, size, step);
        delete[] arr;
        std::cout << "Результат работы программы: " << res << '\n';
    }
	return 0; 
}