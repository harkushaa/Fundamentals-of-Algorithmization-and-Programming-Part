#include <cmath>

using std::abs;

bool isDivisible(int number, int prime) {
    number = abs(number);
    while(number >= prime) {  // O(n)
        number += (~prime + 1); 
    }
    return number == 0;
}

bool isPrime(int x) {
    int c = 0;
    for (unsigned int i = 1; i <= x; ++i) {  // O(n), где n - это x
        if (x % i == 0) {
            c += 1;
        }
        if (c > 2) return false;
    }
    return true;
};