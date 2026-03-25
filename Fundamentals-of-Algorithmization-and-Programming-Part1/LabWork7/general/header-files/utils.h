#pragma once
#include <string>

#include "./constants.h"

using std::string;

string IntToBinary(const string& s);

inline int readIntegerInLine() {
    int inputValue;
    if (!(std::cin >> inputValue) || (std::cin.peek() != '\n')) {
        std::cin.clear();
        // O(n), где n - количество символов во входном потоке до символа '\n'.
        while (std::cin.get() != '\n') { 
        }
        return -INF;
    }
    return inputValue;
};

inline string readIntStringInLine() {
  string inputValue;
  std::cin >> inputValue;  // O(n), где n - длина введенной строки.
  if (inputValue[0] == '-' || isdigit(inputValue[0])) {
    unsigned int size = inputValue.size();
    // O(n), где n - длина строки.
    for (unsigned int i = 1; i < size; ++i) {
      if (!isdigit(inputValue[i])) {
        return INFSTRING;
      }
    }
  }  
  else return INFSTRING; 
  return inputValue;
};