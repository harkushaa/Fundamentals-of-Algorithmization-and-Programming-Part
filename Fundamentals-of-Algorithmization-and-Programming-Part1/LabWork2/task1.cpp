#include <iostream>

int main() {
    double x;
    std::cout << "Enter x value: ";
    std::cin >> x;
    double x_sqrt = x * x; // 1
    double p1;
    p1 = x * (69 * x_sqrt + 8); // 2 - 3 - 4
    double p2;
    p2 = 23 * x_sqrt + 32; // 5 - 6
    std::cout << "First result: " << p1 + p2 << '\n'; // 7
    std::cout << "Second result: " << p1 - p2 << '\n'; // 8
    return 0;
}