#include "employee_functions.h"
#include "binary.h"
#include "algorithms.h"
#include "./elastic-search/api.h"

int main() {
    std::cout << "Лабораторная работа 8.\n"
                 "Выполнил Гаркуша Игорь Вячеславович, студент группы 453502\n"
                 "Задание 1. Реализовать программу для управления сотрудниками фирмы.\n";
    DeleteAllEmployeesInIndex();
    int n = 0;
    employee *arr = nullptr;
    loadDatabase(arr, n);
    AddAllEmployeesFromArray(arr, n); 
    while (true) {
        std::cout << "Введите номер операции, которую хотите выполнить:\n"
                     "0: Завершить работу программы.\n"
                     "1: Поиск сотрудников.\n"
                     "2: Просмотреть записи о сотрудниках.\n"
                     "3: Отсортировать сотрудников по возрастанию зарабатанной платы.\n"
                     "4: Добавить запись о новом сотруднике.\n"
                     "5: Удалить запись о сотруднике.\n"
                     "6: Изменить запись о сотруднике.\n"   
                     "7: Очистить бинарный файл.\n"; 
        int choice;
        std::cin >> choice;
        std::cout << "--------------------------------------------------\n";
        switch (choice) {
            case 1:
                SearhViaElastic(arr, n);
                break;
            case 2:
                displayDatabase();
                break;
            case 3:
                BubbleSortAndShow(arr, n);
                break;
            case 4:
                addToDatabase(arr, n);
                break;
            case 5:
                deleteFromDatabase(arr, n);
                break;
            case 6:
                editDatabase(arr, n);
                break;
            case 7:
                clearDatabase(arr, n);
                break;
            default:
                free(arr);
                return 0;
        }
        std::cout << "--------------------------------------------------\n";
    }
}