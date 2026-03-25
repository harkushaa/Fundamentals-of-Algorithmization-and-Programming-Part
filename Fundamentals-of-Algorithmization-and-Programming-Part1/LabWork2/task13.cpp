#include <iostream>

long double sqrtBinarySearch(long double x) {
    if (x < 0) {return -1;}
    if (x == 0) {return 0;}

    long double low = 0, high = x;
    long double tolerance = 1e-10;

    if (x < 1) {high = 1;}

    std::cout << "low: " << low << '\n';
    std::cout << "high: " << high << '\n';

    while (high - low > tolerance) {
        std::cout << "low: " << low << '\n';
        std::cout << "high: " << high << '\n';
        long double mid = (low + high) / 2.0;
        if (mid * mid < x) {
            low = mid;
        } else {
            high = mid;
        }
    }
    return (low + high) / 2.0;
}

int main() {
    double x;
    std::cout << "Enter x: ";
    std::cin >> x;
    std::cout << '\n';
    sqrtBinarySearch(x);
    return 0;
}