#include <iostream>
#include <limits>
#include <pqxx/pqxx>
#include <string>
#include <cctype>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <ctime>    
#include <nlohmann/json.hpp>

#include "../../constants/constants.h"

using std::string;

inline bool IsValidNumber(const std::string& input) {
    for (char c : input) {
        if (!std::isdigit(c)) {
            return false; 
        }
    }
    return true; 
};

inline bool IsRange(const std::string& input) {
    unsigned int dashPos = input.find('-');
    if (dashPos == std::string::npos) {
        return false; 
    }
    
    std::string left = input.substr(0, dashPos);
    std::string right = input.substr(dashPos + 1);
    
    return IsValidNumber(left) && IsValidNumber(right); 
};

inline bool convertToBoolean(const std::string& value) {
    return value == "1" || value == "true";
};

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

inline double ReadDoubleInLine() {
    double inputValue;
    if (!(std::cin >> inputValue) || (std::cin.peek() != '\n')) {
        std::cin.clear();
        while (std::cin.get() != '\n') {  
        }
        return -INF; 
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  
    return inputValue;
}

inline bool ValidIntegerString(string& inputValue) {
  for (unsigned int i = 0; i < inputValue.size(); ++i) {
    if (!isdigit(inputValue[i])) {
      return false;
    }
  }
  return true;
};

inline bool ValidFloatString(string& inputValue) {
    int dotCount = 0; 
    if (inputValue.empty()) { 
        return false;
    }
    for (unsigned int i = 0; i < inputValue.size(); ++i) {
        if (inputValue[i] == '.') { 
            dotCount++;
            if (dotCount > 1) { 
                return false;
            }
        } else if (!isdigit(inputValue[i])) {
            return false;
        }
    }
    if (dotCount == 0) { 
        return false;
    }
    return true; 
};

inline bool isValidGrade(string& grade_str) {
    if (!ValidIntegerString(grade_str)) return false;

    int grade = std::stoi(grade_str);
    return grade >= 1 && grade <= 10;
}

inline void getGrades(string& grades_str) {
    string input;
    bool first_input = true;

    while (true) {
        std::cout << "Введите оценку (от 1 до 10), или введите STOP для завершения: ";
        std::getline(std::cin, input);

        if (input == "STOP" || input == "stop") {
            break; 
        }

        if (isValidGrade(input)) {
            if (!first_input) {
                grades_str += " ";
            }
            grades_str += input;  
            first_input = false;  
        } else {
            std::cout << "Ошибка ввода! Оценка должна быть целым числом от 1 до 10." << '\n';
        }
    }
}

inline bool CheckValidID(pqxx::work& txn, const int applicantId) {
    pqxx::result res = txn.exec(
        "SELECT applicant_id FROM public.applicants WHERE applicant_id = " + txn.quote(applicantId) + " LIMIT 1"
    );
    return !res.empty();
}

inline bool CompareByFullname(const nlohmann::json& a, const nlohmann::json& b) {
    return a["_source"]["fullname"].get<string>() < b["_source"]["fullname"].get<string>();
};