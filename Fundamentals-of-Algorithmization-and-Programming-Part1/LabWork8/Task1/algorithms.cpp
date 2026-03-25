#include "algorithms.h"

void BubbleSortAndShow(employee* arr, int n) {
    int sal1, sal2;
    for (int i = 0; i < n - 1; i++) { 
        for (int j = 0; j < n - i - 1; j++) {  
            sal1 = arr[j].currency ? arr[j].salary_per_hour.dollars : arr[j].salary_per_hour.euros;
            sal2 = arr[j + 1].currency ? arr[j + 1].salary_per_hour.dollars : arr[j + 1].salary_per_hour.euros;

            if (arr[j].hours_worked * sal1 > arr[j + 1].hours_worked * sal2) {
                std::swap(arr[j], arr[j + 1]); 
            }
        }
    }

    for (int i = 0; i < n; i++) {
        sal1 = (arr[i].currency ? arr[i].salary_per_hour.dollars : arr[i].salary_per_hour.euros) * arr[i].hours_worked;
        std::cout << "["        << arr[i].fullname << "]: "
                 "[Табельный номер: " << arr[i].service_number << "] "
                 "[Рабочие часы: " << arr[i].hours_worked << "] "
                 "[Зарплата: "  << sal1 << "]\n";
    }
}

bool isServiceNumberUnique(const employee* arr, int n, const int service_number) {
    for (int i = 0; i < n; ++i) {
        if (arr[i].service_number == service_number) {
            return false; 
        }
    }
    return true; 
}

bool IsValidNumber(const std::string& input) {
    for (char c : input) {
        if (!std::isdigit(c)) {
            return false; 
        }
    }
    return true; 
}

bool IsRange(const std::string& input) {
    unsigned int dashPos = input.find('-');
    if (dashPos == std::string::npos) {
        return false; 
    }
    
    std::string left = input.substr(0, dashPos);
    std::string right = input.substr(dashPos + 1);
    
    return IsValidNumber(left) && IsValidNumber(right); 
}
