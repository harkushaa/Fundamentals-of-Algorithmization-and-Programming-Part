#include "employee_functions.h"
#include "algorithms.h"

void read(employee*& arr, int& n, employee& e) {
    std::cout << "Введите ФИО сотрудника: ";
    std::cin.ignore(); 
    std::cin.getline(e.fullname, sizeof(e.fullname));

    int service_number;
    while (true) {
        std::cout << "Введите табельный номер сотрудника: ";
        service_number = ReadIntegerInLine();
        if (service_number < 0) {
            std::cout << "Некорректный ввод.\n";
            continue;
        }
        e.service_number = service_number;
        if (!isServiceNumberUnique(arr, n, e.service_number)) {
            std::cout << "Табельный номер уже существует. Попробуйте другой.\n";
            continue;
        }
        break;
    }
    
    int hours_worked;
    while (true) {
        std::cout << "Введите количество отработанных часов: ";
        hours_worked = ReadIntegerInLine();
        if (hours_worked < 0) {
            std::cout << "Некорректный ввод.\n";
            continue;
        }   
        e.hours_worked = hours_worked;
        break;
    }

    int choice;
    while (true) {
        std::cout << "Введите в какой валюте ЗП (для выбора долларов - 1 | евро - 0): ";
        choice = ReadIntegerInLine();
        if (choice != 0 && choice != 1) {
            std::cout << "Некорректный ввод. Введите 1 либо 0.\n";
            continue;
        }   
        e.currency = choice;
        break;
    }

    int payment;
    while (true) {
        std::cout << "Введите почасовой тариф: ";
        payment = ReadIntegerInLine();
        if (payment < 0) {
            std::cout << "Некорректный ввод.\n";
            continue;
        }   
        if (e.currency) e.salary_per_hour.dollars = payment;
        else e.salary_per_hour.euros = payment;
        break;
    }
}

void display(employee& e) {
    std::cout << "["        << e.fullname << "]: "
                 "[Табельный номер: " << e.service_number << "] "
                 "[Рабочие часы: " << e.hours_worked << "] "
                 "[ЗП за час: "  << (e.currency ? e.salary_per_hour.dollars : e.salary_per_hour.euros) << "]\n";
}

void changeField(employee*& arr, int& n, employee& e) {
    std::cout << "Введите номер поля, которое хотите изменить:\n"
                 "1: ФИО\n2: Табельный номер\n3: Рабочие часы\n4: Валюта\n5: ЗП за час\n";
    int type;
    while (true) {
        type = ReadIntegerInLine();
        if (type != 1 && type != 2 && type != 3 && type != 4 && type != 5) {
            std::cout << "Некорректный ввод.\n";
            continue;
        }   
        break;
    }
    switch (type) {
        case 1:
            std::cout << "Введите новое ФИО сотрудника: ";
            std::cin.getline(e.fullname, sizeof(e.fullname));
            break;
        case 2:
            int service_number;
            while (true) {
                std::cout << "Введите новый табельный номер сотрудника: ";
                service_number = ReadIntegerInLine();
                if (service_number < 0) {
                    std::cout << "Некорректный ввод.\n";
                    continue;
                }
                e.service_number = service_number;

                if (!isServiceNumberUnique(arr, n, e.service_number)) {
                    std::cout << "Табельный номер уже существует. Попробуйте другой.\n";
                    continue;
                }
                break;
            }
            break;
        case 3:
            int hours_worked;
            while (true) {
                std::cout << "Введите новое количество отработанных часов: ";
                hours_worked = ReadIntegerInLine();
                if (hours_worked < 0) {
                    std::cout << "Некорректный ввод.\n";
                    continue;
                }   
                e.hours_worked = hours_worked;
                break;
            }
            break;
        case 4:
            int choice;
            while (true) {
                std::cout << "Введите в какой валюте ЗП (для выбора долларов - 1 | евро - 0): ";
                choice = ReadIntegerInLine();
                if (choice != 0 && choice != 1) {
                    std::cout << "Некорректный ввод. Введите 1 либо 0.\n";
                    continue;
                }   
                e.currency = choice;
                break;
            }
            break;
        case 5:
            int payment;
            while (true) {
                std::cout << "Введите новый почасовой тариф: ";
                payment = ReadIntegerInLine();
                if (payment < 0) {
                    std::cout << "Некорректный ввод.\n";
                    continue;
                }   
                if (e.currency) e.salary_per_hour.dollars = payment;
                else e.salary_per_hour.euros = payment;
                break;
            }
            break;
        default:
            std::cout << "Некорректный ввод от 1 до 5.";
            break;
    }
}