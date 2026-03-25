#include <iostream>
#include <string>
#include <algorithm>

#include "../../general/header-files/constants.h"

using std::string;

void ConvertToForwardModifiedCode(string& bit_sequence1, string& bit_sequence2) {
    if (bit_sequence1[0] == '1') bit_sequence1 = '1' + bit_sequence1; // O(n), где n - длина строки bit_sequence1
    else bit_sequence1 = '0' + bit_sequence1; // O(n)

    if (bit_sequence2[0] == '1') bit_sequence2 = '1' + bit_sequence2; // O(n), где n - длина строки bit_sequence2
    else bit_sequence2 = '0' + bit_sequence2; // O(n)
}

void ConvertBothToEqualSizes(string& big_string, string& small_string, unsigned int sizes_difference) {
    for (unsigned int i = 1; sizes_difference != 0; sizes_difference--) {  // O(n), где n - разница в размерах строк
        small_string.insert(i, 1, '0'); // O(n), где n - длина строки small_string
    }
};

void CallConvertBothToEqualSizes(string& bit_sequence1, unsigned int size1, string& bit_sequence2, unsigned int size2) {
    unsigned int sizes_difference;
    if (size1 == size2) return;
    else if (size1 > size2) {
        sizes_difference = size1 - size2;
        ConvertBothToEqualSizes(bit_sequence1, bit_sequence2, sizes_difference);  // O(n^2)
    }
    // (size1 < size2)
    else {
        sizes_difference = size2 - size1;
        ConvertBothToEqualSizes(bit_sequence2, bit_sequence1, sizes_difference);  // O(n^2)
    }
};

void ForwardModifiedToAdditionalModified(string& bit_sequence, unsigned int size, unsigned int indx = 2) {
    for (unsigned int i = indx; i < size; ++i) {  // O(n), где n - длина строки bit_sequence
        if (bit_sequence[i] == '0') bit_sequence[i] = '1';
        else bit_sequence[i] = '0';
    }
    bool remainder = true;
    unsigned int r = indx - 1;
    for (unsigned int i = size - 1; i > r; i--) {  // O(n)
        if (bit_sequence[i] == '0') {
            if (!remainder) {
                bit_sequence[i] = '1';
                break;
            }
            else {
                bit_sequence[i] = '1';
                break;
            }
        }
        else if (bit_sequence[i] == '1') {
            if (!remainder) {
                break;
            }
            else {
                remainder = true;
                bit_sequence[i] = '0';
            }
        }
    }
};

void GenerateResult(bool& remainder, const string& bit_sequence1, const string& bit_sequence2, string& bit_sequence3, const int size) {
    remainder = false;
    for (int i = size - 1; i > -1; --i) {  // O(n)
        if (!remainder) {
            if (bit_sequence1[i] == '0') {
                if (bit_sequence2[i] == '1') bit_sequence3 = bit_sequence3 + '1';
                else bit_sequence3 = bit_sequence3 + '0'; 
            }
            else {
                if (bit_sequence2[i] == '1') {
                    bit_sequence3 = bit_sequence3 + '0';
                    remainder = true;
                }
                else bit_sequence3 = bit_sequence3 + '1';
            }
        }
        else {
            if (bit_sequence1[i] == '0') {
                if (bit_sequence2[i] == '1') bit_sequence3 = bit_sequence3 + '0';
                else {
                    bit_sequence3 = bit_sequence3 + '1';
                    remainder = false;
                }
            }
            else {
                if (bit_sequence2[i] == '1') bit_sequence3 = bit_sequence3 + '1';
                else bit_sequence3 = bit_sequence3 + '0';
            }
        }
    }
    std::reverse(bit_sequence3.begin(), bit_sequence3.end());  // O(n), где n - длина строки полученной
}

string CalculateInAdditionalCode(string& bit_sequence1, string& bit_sequence2) {
    if (bit_sequence1[0] == '1') ForwardModifiedToAdditionalModified(bit_sequence1, bit_sequence1.size(), 2);  // O(n), где n - длина строки bit_sequence1
    if (bit_sequence2[0] == '1') ForwardModifiedToAdditionalModified(bit_sequence2, bit_sequence2.size(), 2);  // O(n), где n - длина строки bit_sequence2

    const int size = bit_sequence1.size();
    string bit_sequence3;

    std::cout << "Первое число в модифицированном доп. коде:\n" << bit_sequence1[0] << bit_sequence1[1] << '.';
    std::cout << bit_sequence1.substr(2) << '\n';  // O(n), где n - длина строки bit_sequence1
    std::cout << "Второе число в модифицированном доп. коде:\n" << bit_sequence2[0] << bit_sequence2[1] << '.';
    std::cout << bit_sequence2.substr(2) << '\n';  // O(n), где n - длина строки bit_sequence2

    bool remainder;
    if (bit_sequence1[0] == '1' && bit_sequence2[0] == '1' || bit_sequence1[0] == '0' && bit_sequence2[0] == '0') {
        GenerateResult(remainder, bit_sequence1, bit_sequence2, bit_sequence3, size);  // O(n), где n - длина строки bit_sequence1
        if (bit_sequence3[0] == '0' && bit_sequence3[1] == '1' || bit_sequence3[0] == '1' && bit_sequence3[1] == '0') return INFSTRING;
        else {
            unsigned int difference = size - bit_sequence3.size();
            //результат сложения положительный
            if (bit_sequence3[0] == '0') return bit_sequence3;
            //результат сложения отрицательный (инверсия + 1)
            else {
                //повторное использование функции той же функции => инверсия + 1
                ForwardModifiedToAdditionalModified(bit_sequence3, bit_sequence3.size(), difference + 2);  // O(n), где n - длина строки bit_sequence3
                return bit_sequence3;
            }
        }
    }
    else {
        GenerateResult(remainder, bit_sequence1, bit_sequence2, bit_sequence3, size);
        return bit_sequence3;
    }
};
