#pragma once
#include <iostream>
#include <cstring>
#include <cctype>
#include <limits>
#include "employee.h"
#include "employee_functions.h"
#include "constants.h"

void BubbleSortAndShow(employee* arr, int n);

bool isServiceNumberUnique(const employee*, int, const int);
bool IsValidNumber(const std::string&);
bool IsRange(const std::string&);

inline int ReadIntegerInLine() {
    int inputValue;
    if (!(std::cin >> inputValue) || (std::cin.peek() != '\n')) {
        std::cin.clear();
        while (std::cin.get() != '\n') {
        }
        return -INF;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return inputValue;
}