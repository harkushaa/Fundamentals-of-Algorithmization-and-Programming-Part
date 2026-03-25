#include <string>
#include <cmath>

#include "../../general/header-files/constants.h"

using std::string;

void GenerateEncodingForChosenNumberSystem(const unsigned int base, string*& encoding) {
    //заполняем массив строк переданный по ссылке
    for (unsigned int i = 0; i < base; ++i) {  // O(n)
        encoding[i] = string(1, alphabet[i % alphabetSize]) + string(1, digits[i / alphabetSize]);
    }   
}

string ConvertToChosenNumberSystem(const string& number, const unsigned int base, string*& encoding) {
    if (number == "0") {
        return "A0";
    }

    string s = number;

    string res;
    string curr = s;

    while (curr != "0") {  // O(n)
        int remainder = 0;
        string next = "";
        bool leadingZero = true;

        for (char digit : curr) {  // O(m), где m - длина текущего числа 
            int curr_digit = remainder * 10 + (digit - '0');
            int quotient = curr_digit / base;
            remainder = curr_digit % base;

            if (quotient > 0 || !leadingZero) {
                next += (quotient + '0');
                leadingZero = false;
            }
        }
        
        curr = next.empty() ? "0" : next;
        res = encoding[remainder] + res;
    }

    return res;  
}

unsigned int TransformToInteger(char unit1, char unit2) {
    return unit1 - 'A' + (unit2 - '0') * alphabetSize;
}

unsigned int ConvertFromEncodingToInteger(string& number, const unsigned int base) {
    const unsigned int size = number.size();
    
    unsigned int total = 0; 
    for (int i = size - 1, mult = 0; i >= 0; i -= 2, ++mult) {  // O(n)
        total += TransformToInteger(number[i - 1], number[i]) * pow(base, mult);
    }

    return total;
}

string addNumbers(const string& num1, const string& num2, int base, string*& encoding) {
    string result;
    int carry = 0;

    string a = num1, b = num2;
    string add = string(1, alphabet[0]) + string(1, digits[0]);

    //разность может быть отрицательным
    int size1 = a.size() / 2, size2 = b.size() / 2;
    int size_difference = abs(size1 - size2);

    if (a.size() > b.size()) {
        for (unsigned int i = size_difference; i > 0; --i) {  // O(n)
            b = add + b;
        }
    } else if (a.size() < b.size()) {  
        for (unsigned int i = size_difference; i > 0; --i) { // O(n)
            a = add + a;
        }
    }

    for (int i = a.size() - 1; i >= 0; i -= 2) {  // O(n)
        int sum = TransformToInteger(a[i - 1], a[i]) + TransformToInteger(b[i - 1], b[i]) + carry;
        carry = sum / base; 
        
        result = ConvertToChosenNumberSystem(std::to_string(sum % base), base, encoding) + result; 
    }

    // Добавление переноса, если он остался
    if (carry > 0) result = ConvertToChosenNumberSystem(std::to_string(carry), base, encoding) + result; 

    return result;
}

string subtractNumbers(const string& num1, const string& num2, int base, string*& encoding) {
    string result;
    int borrow = 0;

    string add = string(1, alphabet[0]) + string(1, digits[0]);

    string a = num1, b = num2;
    for (unsigned int i = (a.size() - b.size()) / 2; i > 0; --i) {
        b = add + b;
    }

    for (int i = a.size() - 1; i >= 0; i -=2) {
        int diff = TransformToInteger(a[i - 1], a[i]) - TransformToInteger(b[i - 1], b[i]) - borrow;
        if (diff < 0) {
            diff += base; // Добавляем основание, если заем
            borrow = 1;
        } else {
            borrow = 0;
        }

        result = ConvertToChosenNumberSystem(std::to_string(diff), base, encoding) + result; 
    }

    return result;
}

string proccessOperation(string& num1, string& num2, string*& encoding, const unsigned int base, bool isAddition) {
    bool isNegative1 = (num1[0] == '-');
    bool isNegative2 = (num2[0] == '-');

    string absNum1 = isNegative1 ? num1.substr(1) : num1;  // O(n)
    string absNum2 = isNegative2 ? num2.substr(1) : num2;  // O(n)

    if (isAddition) {
        if (isNegative1 == isNegative2) {
            // Оба числа одного знака
            string result = addNumbers(absNum1, absNum2, base, encoding);
            return (isNegative1 ? "-" : "") + result;
        } else {
            // Числа разных знаков
            if (ConvertFromEncodingToInteger(absNum1, base) >= ConvertFromEncodingToInteger(absNum2, base)) {
                string result = subtractNumbers(absNum1, absNum2, base, encoding);
                return (isNegative1 ? "-" : "") + result;
            } else {
                string result = subtractNumbers(absNum2, absNum1, base, encoding);
                return (isNegative2 ? "-" : "") + result;
            }
        }
    } else {
        if (isNegative1 != isNegative2) {
            // Числа разных знаков
            string result = addNumbers(absNum1, absNum2, base, encoding);
            return (isNegative1 ? "-" : "") + result;
        } else {
            // Оба числа одного знака
            if (ConvertFromEncodingToInteger(absNum1, base) >= ConvertFromEncodingToInteger(absNum2, base)) {
                string result = subtractNumbers(absNum1, absNum2, base, encoding);
                return (isNegative1 ? "-" : "") + result;
            } else {
                string result = subtractNumbers(absNum2, absNum1, base, encoding);
                return (isNegative1 ? "" : "-") + result;
            }
        }
    }
}