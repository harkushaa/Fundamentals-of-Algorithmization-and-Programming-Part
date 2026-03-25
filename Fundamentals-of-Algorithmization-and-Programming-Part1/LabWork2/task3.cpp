#include <iostream>

int main () {
    double n = 6;
    double q = 1 / (n + 1);
    std::cout << "Please enter b1 value: ";
    double b1;
    std::cin >> b1;
    double res;
    res = b1 / (1 - q);
    std::cout << res;
    return 0;
}